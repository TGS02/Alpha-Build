#include "Player.h"
#include "TextureManager.h"
#include <iostream>
#include "Map.h"
#include <algorithm>
using namespace std;
#define GRAV 8.0
#define JUMPFORCE 20.0
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60


Player::Player():m_iSpeed(5), m_src{ 0, 0, 32, 64 }, g_iKeystates(SDL_GetKeyboardState(nullptr)), m_dst{ m_src.w+10, HEIGHT - 5*32-m_src.h -10, m_src.w, m_src.h}
{
	    m_frame = 0,
		m_frameMax = 12,
		m_sprite = 0,
		m_spriteMax = 6;
		left = false;
		onGround = false;
		gravity = 0.04f;
		die = false;
		score = false;
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
		m_dAccelX = m_dAccelY = m_dVelX = m_dVelY = 0.0;
		m_dGrav = GRAV;
		m_dMaxAccelX = 2.0;
		m_dMaxVelX = 6.0;
		m_dMaxVelY = m_dGrav;
		m_dDrag = 0.9;
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



void Player::playerUpdate(Map *map, Uint32 delta)
{
	if (!stop)
	{

		m_dAccelX = min(max(m_dAccelX, -(m_dMaxAccelX)), (m_dMaxAccelX));
		// Set and clamp X velocity.
		m_dVelX = (m_dVelX + m_dAccelX) * m_dDrag;
		m_dVelX = min(max(m_dVelX, -(m_dMaxVelX)), (m_dMaxVelX));
		m_dst.x += (int)m_dVelX;
		// Now do Y axis.
		m_dVelY += m_dAccelY + (m_dGrav / 6); // Adjust gravity to get slower jump.
		m_dVelY = min(max(m_dVelY, -(m_dMaxVelY * 10)), (m_dMaxVelY));
		m_dst.y += (int)m_dVelY;
	}
	checkCollision(m_dVelX, m_dVelY, map);	
	checkBound();
	animate();

}

glm::vec2 Player::getPosition()
{
	return glm::vec2(m_dst.x, m_dst.y);
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
	return  die;
}

void Player::setRotation(bool newRot)
{
	left = newRot;
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

void Player::checkCollision(int x, int y, Map* map)
{
	SDL_Rect tile;
	SDL_Rect newDst;
	score = false;
	int type = 0, top = 0, left = 0, right = 0, bottom = 0;
	for (int row = 0; row < 24; row++)
	{
		for (int column = 0; column < 32; column++)
		{
			type = map->colMap[row][column];
			top = row * 32;
			bottom = row * 32 + 32;
			left = column * 32;
			right = column * 32 + 32;
			SDL_Rect tile = { left,top,32,32 };
			SDL_Rect newDst = { m_dst.x + 5,m_dst.y,m_dst.w / 2, m_dst.h };
			if (type == 1) {//Solid tile
				if (SDL_HasIntersection(&newDst, &tile)) {
					if ((m_dst.y + m_dst.h) - GetVelY() <= tile.y)
					{ // Collision from top.
						SetGrounded(true);
						SetVelY(0.0); // Stop the player from moving vertically. We aren't modifying gravity.
						SetY(tile.y - m_dst.h );
					}
					else if (m_dst.y - GetVelY() >= (tile.y + tile.h))
					{ // Collision from bottom.
						SetVelY(0.0); // Stop the player from moving vertically. We aren't modifying gravity.
						SetY(tile.y + tile.h );
					}
					else if ((m_dst.x  ) - GetVelX() <= tile.x)
					{ // Collision from left.
						SetVelX(0.0); // Stop the player from moving horizontally.
						SetX(tile.x - m_dst.w);
					}
					else if (m_dst.x + m_dst.w/2- GetVelX() >= (tile.x +tile.w))
					{ // Collision from right.
						SetVelX(0.0); // Stop the player from moving horizontally.
						SetX(tile.x + tile.w + 0.01f);
					}
					
				}

			}
			tile = { left + 1,top,30,10 };
			newDst = { m_dst.x + 5,m_dst.y + 16 * m_dst.h / 17,m_dst.w/2 , m_dst.h / 16 };
			if (type == 2) {//platform
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						if ((m_dst.y + m_dst.h) - GetVelY() <= tile.y)
						{ // Collision from top.
							SetGrounded(true);
							SetVelY(0.0); // Stop the player from moving vertically. We aren't modifying gravity.
							SetY(tile.y - m_dst.h);
						}
						
					}
				}
			}
			newDst = { m_dst.x + 5,m_dst.y ,m_dst.w - 5, 3*m_dst.h/4};
			tile = { left  ,top + 15,32,17 };
			if (type == 4) //Acid1
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}
			}
			newDst = { m_dst.x ,m_dst.y ,m_dst.w , m_dst.h  };
			tile = { left  ,top ,32,32 };
			if(type==5)// Acid2
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}

			}
			newDst = { m_dst.x+5 ,m_dst.y ,m_dst.w-5 , m_dst.h };
			tile = { left  ,top ,15,30 };
			if (type == 3)//Spike Right
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}

			}
			newDst = { m_dst.x + 5 ,m_dst.y ,m_dst.w - 5 , m_dst.h };
			tile = { left+13  ,top ,16,25 };
			if (type == 6)//Spike left
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}

			}
			newDst = { m_dst.x + 5 ,m_dst.y ,m_dst.w - 5 , m_dst.h };
			tile = { left ,top ,25,15 };
			if (type == 7)//Spike Down
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}

			}
			newDst = { m_dst.x + 5 ,m_dst.y ,m_dst.w - 5 , m_dst.h };
			tile = { left ,top+15 ,25,20 };
			if (type == 8)//Spike up
			{
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						Mix_PlayChannel(-1, Engine::Instance().getDeathMixChunk(), 0);
						die = true;
					}
				}

			}

			newDst = { m_dst.x + 5 ,m_dst.y ,m_dst.w - 5 , m_dst.h };
			tile = { left ,top + 15 ,25,20 };
			if (type == 9)//end
			{

				if (SDL_HasIntersection(&newDst, &tile)) {
					{
						finish = true;
						Mix_PlayChannel(-1, Engine::Instance().getWinMixChunk(), 0);
					}
				}
			}

			newDst = { m_dst.x + 5 ,m_dst.y ,m_dst.w - 5 , m_dst.h };
			tile = { left ,top + 15 ,20,21 };
			if (type == 16)//Pickups
			{
				
				if (SDL_HasIntersection(&newDst, &tile)) {
					{
                       
						score = true;
						record += 10;
						Mix_PlayChannel(-1, Engine::Instance().getMixChunk(), 0);
						map->colMap[row][column]=0;
						map->map[row][column] = 0;
						

					}
				}
				

			}
			
			
		}
	}
}

void Player::playerDraw(SDL_Renderer* g_pRenderer)
{
	if (!left && !die)
		TextureManager::Draw(g_pRenderer, m_pTexture, &m_src, &m_dst);
	if(left && !die)
		TextureManager::DrawLeft(g_pRenderer, m_pTexture, &m_src, &m_dst);
	if(die)
	{
		if (delayMin == delayMax)
		{
			m_dst = { m_src.w, HEIGHT - 5 * 32 - m_src.h  , m_src.w, m_src.h };
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
}

Player::~Player(){}
void Player::clean()
{

	SDL_DestroyTexture(m_pTexture);
}

void Player::MoveX() { m_dAccelX += 1.0 * m_iDir; }// Should change real number to speed variable.

void Player::Stop() // If you want a dead stop both axes.
{
	m_dVelY = 0.0;
	m_dVelX = 0.0;
}

void Player::SetDir(int dir) { m_iDir = dir; } // Will be used to set direction of sprite for your Assignment 2.
void Player::SetAccelX(double a) { m_dAccelX = a; }
void Player::SetAccelY(double a) { m_dAccelY = a; }

bool Player::IsGrounded() { return onGround; }

void Player::SetGrounded(bool g) { onGround = g; }
double Player::GetVelX() { return m_dVelX; }
double Player::GetVelY() { return m_dVelY; }
void Player::SetVelX(double v) { m_dVelX = v; }

void Player::setVelXMax(double v){	m_dMaxVelX = v;}

void Player::setVelyMax(double v){	m_dMaxVelX = v;}

void Player::setDrag(double d){	m_dDrag = d;}

void Player::SetVelY(double v) { m_dVelY = v; }
void Player::SetX(int y) { m_dst.x = y; }
void Player::SetY(int y) { m_dst.y = y; }

void Player::SetLeft(bool l) { left = l; }

bool Player::GetLeft() { return left; }
