#include "Player.h"
#include "TextureManager.h"
#include <iostream>
#include "Map.h"
#include <algorithm>

using namespace std;
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60

void Forces::Clear()
{
	air_control = 0.25f;
	grd_control = 2.5f;
	air_force = { 0.0f, 0.0f };
	grd_force = { 0.0f, 0.0f };
	air_drag = 0.0f;
	grd_drag = 0.0f;
	air_maxSpeed = 0.0f;
	grd_maxSpeed = 0.0f;
	air_maxDrag = 0.0f;
	grd_maxDrag = 0.0f;
	jumpForce = { 0.0f, 0.0f };
	jumpForceMax = 0.0f;
	jumpImpulse = { 0.0f, 0.0f };
	numSupportingTiles = 0;
}

void Forces::Update(TileMap* tileMap)
{
	Clear();

	// Get data from intersecting tiles
	unsigned int numIntersectingTiles = tileMap->getIntersectingTiles()->size();
	for (unsigned int i = 0; i < numIntersectingTiles; i++)
	{
		air_force += tileMap->getIntersectingTiles()->at(i)->getForce();
		air_maxSpeed += tileMap->getIntersectingTiles()->at(i)->getMaxSpeed();
		air_drag += tileMap->getIntersectingTiles()->at(i)->getDrag();
		air_maxDrag += tileMap->getIntersectingTiles()->at(i)->getMaxDrag();
		jumpForce += tileMap->getIntersectingTiles()->at(i)->getJumpForce();
		jumpForceMax += tileMap->getIntersectingTiles()->at(i)->getJumpForceMax();
	}
	if (static_cast<float>(numIntersectingTiles) > 0.0f)
	{
		air_force /= static_cast<float>(numIntersectingTiles);
		air_maxSpeed /= static_cast<float>(numIntersectingTiles);
		air_drag /= static_cast<float>(numIntersectingTiles);
		air_maxDrag /= static_cast<float>(numIntersectingTiles);
		jumpForce /= static_cast<float>(numIntersectingTiles);
		jumpForceMax /= static_cast<float>(numIntersectingTiles);
	}

	// Add or replace data from colliding tiles where appropriate
	numSupportingTiles = tileMap->getSupportingTiles()->size();
	for (unsigned int i = 0; i < numSupportingTiles; i++)
	{
		grd_force += tileMap->getSupportingTiles()->at(i)->getForce() / static_cast<float>(numSupportingTiles);
		grd_maxSpeed += tileMap->getSupportingTiles()->at(i)->getMaxSpeed() / static_cast<float>(numSupportingTiles);
		grd_drag += tileMap->getSupportingTiles()->at(i)->getDrag() / static_cast<float>(numSupportingTiles);
		grd_maxDrag += tileMap->getSupportingTiles()->at(i)->getMaxDrag() / static_cast<float>(numSupportingTiles);
		jumpImpulse += tileMap->getSupportingTiles()->at(i)->getJumpImpulse() / static_cast<float>(numSupportingTiles);
	}
}

Player::Player() :
	m_src{ 0, 0, 32, 64 },
	g_iKeystates(SDL_GetKeyboardState(nullptr)),
	m_dst{ m_src.w+10, HEIGHT - 5*32-m_src.h -10, m_src.w, m_src.h},
	m_col{ 10, 4, 20, 60 },
	m_pos{ static_cast<float>(m_dst.x + m_col.x), static_cast<float>(m_dst.y + m_col.y) },
	isJumping(false),
	m_pTileMap(nullptr)
{
	    m_frame = 0,
		m_frameMax = 12,
		m_sprite = 0,
		m_spriteMax = 6;
		left = false;
		onGround = false;
		die = false;
		delayMin = 0;
		delayMax = 15;
		startFlashing = false;
		flashMin = 0;
		flashMax = 35;
		stopMin = 0;
		stopMax = 100;
		record = 0;
		finish = false;
	/*///////////////////////////*/
		m_iDir = 1;
		stop = false;
}

SDL_Texture* Player::loadPlayer(SDL_Renderer* m_pRenderer)
{
	m_pTexture= TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/CowboyCadet.png");
	return m_pTexture;
}

void Player::animate()
{
	if (m_frame == m_frameMax)
	{
		m_frame = 0; // Roll the frame ctr back to 0.
		m_sprite++; // Increment the sprite index.
		if (m_sprite == m_spriteMax)
			m_sprite = 0;
		m_src.x = 32 * m_sprite; // Set the new src x.
	}
	m_frame++; // Increment frame counter.
}

bool Player::keyDown(SDL_Scancode c)
{
	if (g_iKeystates != nullptr)
	{
		if (g_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Player::playerUpdate()
{
	// Populate the intersection vector, then prepare forces from intersecting tiles
	m_pTileMap->checkIntersection(getCol());
	m_forces.Update(m_pTileMap);

	// Accelerate, move, check collisions, and set final position
	accelerate();
	move();
	
	// Update the player's weapon and sprite
	m_pWeapon->Update();
	animate();

	Engine::Instance().getCamera().UpdatePosition({ static_cast<int>(m_pos.x) + m_dst.w / 2, static_cast<int>(m_pos.y) + m_dst.h / 2 });
}

glm::vec2 Player::getSize()
{
	return glm::vec2(m_dst.w, m_dst.h);
}

bool Player::getRotation()
{
	return left;
}

bool Player::getDie()
{
	return die;
}

void Player::setRotation(bool newRot)
{
	left = newRot;
}

void Player::jump(bool holdingKey)
{
	if (!holdingKey)
	{
		isJumping = false;
	}
	else if (holdingKey && onGround)
	{
		m_fTotalJumpForce = { 0.0f, 0.0f };
		m_fAcceleration += m_forces.jumpImpulse;
		isJumping = true;
		onGround = false;
		std::cout << "Jumping with velocity: " << m_forces.jumpImpulse.x << '/' << m_forces.jumpImpulse.y << '!' << std::endl;
	}
	else if (holdingKey && isJumping && !onGround)
	{
		float squaredTotalJumpForce = (m_fTotalJumpForce.x * m_fTotalJumpForce.x) + (m_fTotalJumpForce.y * m_fTotalJumpForce.y);
		float squaredJumpForceMax = (m_forces.jumpForceMax * m_forces.jumpForceMax);
		if (squaredTotalJumpForce < squaredJumpForceMax)
		{
			m_fAcceleration += m_forces.jumpForce;
			m_fTotalJumpForce += m_forces.jumpForce;
			// Ideally, it would also check how much less than jumpForceMax it is and then limit it to that,
			// but that would require normalizing, which is a lot of extra calculations to be doing every frame.
		}
		else
		{
			isJumping = false; // If you've already reached jumpForceMax, you can't keep accelerating. You might still be going up, though. Remember that this is constantly being counteracted by gravity.
		}
	}
}

void Player::shoot(glm::vec2 direction)
{
	if (m_pWeapon->Fire())
	{
		onGround = false;
		m_fRecoilVelocity -= direction * m_pWeapon->getRecoilForce();
		std::cout << "Firing! " << m_fRecoilVelocity.x << '/' << m_fRecoilVelocity.y << std::endl;
	}
	else
	{
		std::cout << "Unable to fire!" << std::endl;
	}
}

void Player::reload()
{
	if (m_pWeapon->Reload()) {}
}

void Player::checkBound()
{
	if (m_dst.x <= 0)
		m_dst.x = 0;
	if (m_dst.x + m_dst.w >= WIDTH)
		m_dst.x = WIDTH-m_dst.w;
	if (m_dst.y <= 0)
		m_dst.y = 0;
	if (m_dst.y+m_dst.h >= HEIGHT)
		m_dst.y = HEIGHT;
}

void Player::accelerate()
{
	// Accelerate the player
	m_fAcceleration += m_forces.numSupportingTiles > 0 ? m_forces.grd_force + m_forces.air_force : m_forces.air_force;
	m_fVelocity += m_fAcceleration;
	m_fAcceleration = { 0.0f, 0.0f }; // Zero the acceleration in order to make sure it is a blank slate for the next frame.

	// Then apply drag
	m_fVelocity *= m_forces.numSupportingTiles > 0 ? m_forces.grd_drag : m_forces.air_drag;
	float sqaredVelocityMagnitude = (m_fVelocity.x * m_fVelocity.x) + (m_fVelocity.y + m_fVelocity.y);
	float squaredMaxSpeed = m_forces.numSupportingTiles > 0 ? m_forces.grd_maxSpeed * m_forces.grd_maxSpeed : m_forces.air_maxSpeed * m_forces.air_maxSpeed;
	if (sqaredVelocityMagnitude >= squaredMaxSpeed)
		m_fVelocity *= m_forces.numSupportingTiles > 0 ? m_forces.grd_maxDrag : m_forces.air_maxDrag;
	m_fRecoilVelocity *= onGround ? m_forces.grd_drag : m_forces.air_drag;
}

void Player::move()
{
	if (stop)
		return;

	// Record the player's original position, position after translation, and position after adjustment
	glm::vec2 initialPosition = getPosition();
	SDL_Rect initialCollider = getCol();

	glm::vec2 totalVelocity = m_fVelocity + m_fRecoilVelocity;
	glm::vec2 terminalPosition = { initialPosition + totalVelocity };
	SDL_Rect terminalCollider = {
		static_cast<int>(terminalPosition.x),
		static_cast<int>(terminalPosition.y),
		initialCollider.w,
		initialCollider.h };
	
	glm::vec2 finalPosition = terminalPosition;
	SDL_Rect finalCollider = terminalCollider;

	// Check the tileMap for collision at the new position, then compare the player's 'original position' and velocity against each tile that they 'would be colliding with' if in their terminal position
	m_pTileMap->checkCollision(terminalCollider);
	for (unsigned int tileIndex = 0; tileIndex < m_pTileMap->getCollidingTiles()->size(); tileIndex++)
	{
		SDL_Rect tileCollider = m_pTileMap->getCollidingTiles()->at(tileIndex)->getCol();

		switch (m_pTileMap->getCollidingTiles()->at(tileIndex)->getType())
		{
		case StaticTile::Type::SOLID:

			// Player is moving horizontally and is initially neither above nor below the tile
			if (initialCollider.y + initialCollider.h > tileCollider.y &&
				initialCollider.y < tileCollider.y + tileCollider.h)
			{
				// Player is moving left and is right of the tile
				if (totalVelocity.x < 0.0f && initialCollider.x >= tileCollider.x + tileCollider.w)
				{
					m_fVelocity.x = 0.0f;
					m_fRecoilVelocity.y += m_fRecoilVelocity.y > 0 ? -m_fRecoilVelocity.x : m_fRecoilVelocity.x;
					m_fRecoilVelocity.x = 0.0f;
					finalPosition.x = static_cast<float>(tileCollider.x + tileCollider.w);
				}

				// Player is moving right and is left of the tile
				if (totalVelocity.x > 0.0f && initialCollider.x + initialCollider.w <= tileCollider.x)
				{
					m_fVelocity.x = 0.0f;
					m_fRecoilVelocity.y += m_fRecoilVelocity.y > 0 ? m_fRecoilVelocity.x : -m_fRecoilVelocity.x;
					m_fRecoilVelocity.x = 0.0f;
					finalPosition.x = static_cast<float>(tileCollider.x - initialCollider.w);
				}
			}

			// Player is moving vertically and is initially neither to the left nor the right of the tile
			if (initialCollider.x + initialCollider.w > tileCollider.x &&
				initialCollider.x < tileCollider.x + tileCollider.w)
			{
				// Player is moving up and is below the tile
				if (totalVelocity.y < 0.0f && initialCollider.y >= tileCollider.y + tileCollider.h)
				{
					m_fVelocity.y = 0.0f;
					m_fRecoilVelocity.y = 0.0f;
					finalPosition.y = static_cast<float>(tileCollider.y + tileCollider.h);
				}
			}
		case StaticTile::Type::PLATFORM: // Since there is no 'break;', this last check will happen in both cases.
			// Player is moving vertically and is initially neither to the left nor the right of the tile
			if (initialCollider.x + initialCollider.w > tileCollider.x &&
				initialCollider.x < tileCollider.x + tileCollider.w)
			{
				// Player is moving down and is above the tile
				if (totalVelocity.y >= 0.0f && initialCollider.y + initialCollider.h <= tileCollider.y)
				{
					m_fVelocity.y = 0.0f;
					m_fRecoilVelocity.y = 0.0f;
					finalPosition.y = static_cast<float>(tileCollider.y - initialCollider.h);
					onGround = true;
				}
			}

			break;
		case StaticTile::Type::IGNORE:
		default: break;
		}
	}

	// Actually move the player
	m_pos = finalPosition;
	finalCollider.x = static_cast<int>(finalPosition.x); // Adjust the final collision rectangle based on the final position
	finalCollider.y = static_cast<int>(finalPosition.y);
	m_dst.x = static_cast<int>(m_pos.x) - m_col.x; // Move the player's sprite based on their overall position and the difference between their sprites' and colliders' x and y values
	m_dst.y = static_cast<int>(m_pos.y) - m_col.y;

	// Check the tileMap for interaction now that the player is at the final position.
	m_pTileMap->checkInteraction(finalCollider);
	for (unsigned int tileIndex = 0; tileIndex < m_pTileMap->getInteractingTiles()->size(); tileIndex++)
	{
		switch (m_pTileMap->getInteractingTiles()->at(tileIndex)->getType())
		{
		case InteractiveTile::Type::IGNORE:
			break;
		case InteractiveTile::Type::DIE:
			die = true;
			break;
		case InteractiveTile::Type::GET:

			break;
		case InteractiveTile::Type::WIN:
			finish = true;
			break;
		default:
			break;
		}
	}
}

void Player::playerDraw(SDL_Renderer* g_pRenderer)
{
	SDL_RendererFlip flip = left ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	int alpha = 255;

	if(die)
	{
		if (delayMin == delayMax)
		{
			m_pos = { m_src.w, HEIGHT - 5 * 32 - m_src.h };
			std::cout << m_pos.x << m_pos.y << std::endl;
			m_dst = { static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_src.w, m_src.h };
			left = false;
			die = false;
			velY = 0;
			velX = 0;
			onGround = true;
			delayMin = 0;
			startFlashing = true;
		}
		delayMin++;
	}

	if (startFlashing)
	{
		if (stopMin!=stopMax)
		{
			if (flashMin == flashMax / 2)
			{
				SDL_SetTextureAlphaMod(m_pTexture, 32);
				TextureManager::Draw(g_pRenderer, m_pTexture, &m_src, &m_dst);
			}
			if (flashMin == flashMax)
			{
				SDL_SetTextureAlphaMod(m_pTexture, 255);
				TextureManager::Draw(g_pRenderer, m_pTexture, &m_src, &m_dst);
				flashMin = 0;
			}
			flashMin++;
			stopMin++;
		}
		if (stopMin == stopMax)
		{
			SDL_SetTextureAlphaMod(m_pTexture, 255);
			TextureManager::Draw(g_pRenderer, m_pTexture, &m_src, &m_dst);
			startFlashing = false;
			stopMin = 0;
		}
	}

	Engine::Instance().getCamera().RenderOffset(Engine::Instance().GetRenderer(), m_pTexture, &m_src, &m_dst, 0.0, alpha, nullptr, flip);
}

Player::~Player(){}
void Player::clean()
{

	SDL_DestroyTexture(m_pTexture);
}

void Player::Stop() // If you want a dead stop both axes.
{
	m_fVelocity = { 0.0f, 0.0f };
}

void Player::SetDir(int dir) { m_iDir = dir; } // Will be used to set direction of sprite for your Assignment 2.

bool Player::IsGrounded() { return onGround; }

void Player::SetGrounded(bool g) { onGround = g; }

void Player::SetX(int y) { m_dst.x = y; }
void Player::SetY(int y) { m_dst.y = y; }

void Player::SetLeft(bool l) { left = l; }

bool Player::GetLeft() { return left; }