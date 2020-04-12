#include "Gun.h"
#include "TextureManager.h"
#include "Util.h"
#include <glm/vec2.hpp>
#include <ostream>
#include <iostream>
#define WIDTH 1024
#define HEIGHT 768
void Gun::m_changeDirection()
{
	float x = cos(m_currentHeading * Util::Deg2Rad);
	float y = sin(m_currentHeading * Util::Deg2Rad);
	m_VCurrentDirection = glm::vec2(x, y);

}


Gun::Gun(glm::vec2 playerPos)
{
	recoilDrag = glm::vec2(8.0, 0.8);
	m_vPosition = playerPos;
	m_src = { 0,0,40,14 };
	left = false;
	m_turnRate = 20.0f; // 20 degrees per frame
	m_currentHeading = 0.0; //current facing angle
	m_VCurrentDirection = glm::vec2(1.0f, 0.0f);
	m_vVelocity = glm::vec2(0.0f, 0.0f);
	m_speed = 2.9f;
	angleToMouse = 0;
	delayMin = 0;
	delayMax = 15;
	startFlashing = false;
	flashMin = 0;
	flashMax = 35;
	stopMin = 0;
	stopMax = 100;
	playerDie = false;
	counterShoot = 0;
	drawShoot = false;
}

SDL_Texture* Gun::loadGun(SDL_Renderer* m_pRenderer)
{
	
	m_pTexture = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Gun.png");
	return m_pTexture;
	
}

glm::vec2 Gun::getVelocity()
{
	return m_vVelocity;
}

void Gun::setMousePosition(glm::vec2 newPosition)
{
	m_vMousePosition = newPosition;
}

void Gun::setRotation(bool newRot)
{
	left = newRot;
}

void Gun::checkInMouseDirecion()
{
	if (m_vMouseDirection==getCurrentDirection())
	{
		m_speed = 0;
	}
}

void Gun::computeMouseDirection()
{
	glm::vec2 velocity;
	// Obtain the position of the player on the screen
	SDL_Rect position = { m_vPosition.x, m_vPosition.y, 0, 0 };
	position = Engine::Instance().getCamera().Offset(position);
	velocity.x = getMousePosition().x - static_cast<int>(position.x);
	velocity.y = getMousePosition().y - static_cast<int>(position.y);
	m_vMouseDirection = Util::normalize(velocity);
	if (velocity.x < 0) {
		flip = SDL_FLIP_VERTICAL;
		left = true;
	}
	else {
		flip = SDL_FLIP_NONE;
		left = false;
	}
}

void Gun::getShootFsm(bool shoot)
{
	drawShoot = shoot;
}

glm::vec2 Gun::getMousePosition()
{
	return  m_vMousePosition;
}

bool Gun::getRotation()
{
	return left;
}

void Gun::getPlayerDie(bool m_hasDied)
{
	playerDie = m_hasDied;
}

glm::vec2 Gun::getCurrentDirection()
{
	return m_VCurrentDirection;
}


void Gun::setPosition(glm::vec2 newPosition)
{
	m_vPosition = newPosition;
}

glm::vec2 Gun::getPosition()
{
	return m_vPosition;
}

void Gun::setVelocity(glm::vec2 newVelocity)
{
	m_vVelocity = newVelocity;
}

void Gun::turnRight()
{
	float angleDifference = abs(m_turnRate - abs(angleToMouse)) * 0.2f;
	if (angleDifference < 0.25f) angleDifference = 0.0f;
	
	m_currentHeading += ((angleDifference < m_turnRate) ? angleDifference : m_turnRate) * m_speed;
	//m_currentHeading += m_turnRate*m_speed;

}
void Gun::turnLeft()
{
	float angleDifference = abs(m_turnRate - abs(angleToMouse)) * 0.2f;
	if (angleDifference < 0.25f) angleDifference = 0.0f;
	
	m_currentHeading -= ((angleDifference < m_turnRate) ? angleDifference : m_turnRate) * m_speed;

	//  m_currentHeading -= m_turnRate* m_speed;
}

void Gun::draw(SDL_Renderer* g_p_renderer)
{
	
		if (drawShoot)
		{

			m_src = { 40,0,40,14 };
			counterShoot++;
			if (counterShoot == 12)
			{
				counterShoot = 0;
				drawShoot = false;
				m_src = { 0,0,40,14 };

			}

		}
	
	m_dst = { static_cast<int>(m_vPosition.x), static_cast<int>(m_vPosition.y) , 40, 18 };
	SDL_Point centerPoint;
	if (left == false)
		centerPoint = { 0, 9 };
	else
		centerPoint = { -9, 9 };

	if(!playerDie)
	Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, flip);

	if (playerDie)
	{
		if (delayMin == delayMax)
		{
			left = false;
			playerDie = false;
			delayMin = 0;
			startFlashing = true;
		}
		delayMin++;
	}
	if (startFlashing)
	{
		if (stopMin != stopMax)
		{
			if (flashMin == flashMax / 2)
			{
				SDL_SetTextureAlphaMod(m_pTexture, 32);
				if (!left )
					Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_NONE);
				else
					Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_VERTICAL);

			}
			if (flashMin == flashMax)
			{
				SDL_SetTextureAlphaMod(m_pTexture, 255);
				if (!left)
					Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_NONE);
				else
					Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_VERTICAL);

				flashMin = 0;
			}
			flashMin++;
			stopMin++;
		}
		if (stopMin == stopMax)
		{
			SDL_SetTextureAlphaMod(m_pTexture, 255);
			if (!left)
				Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_NONE);
			else
				Engine::Instance().getCamera().RenderOffsetEx(m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_VERTICAL);

			startFlashing = false;
			stopMin = 0;
		}
	}
}

void Gun::shoot()
{

	if (Engine::Instance().GetMouseState(0))
	{
			drawShoot = true;
			glm::vec2 offset;


			float angle = 1.0 - abs(m_VCurrentDirection.y);
			if (m_VCurrentDirection.x <= 0)
			{

				offset.x = getPosition().x + recoilDrag.x;
				offset.y = getPosition().y - 10 * recoilDrag.y;

			}
			else
			{
				offset.x = getPosition().x - recoilDrag.x;
				offset.y = getPosition().y - 10 * recoilDrag.y;

			}


			setPosition(offset);
		}
	
	
}

void Gun::update()
{
	move();
	shoot();
}

void Gun::clean()
{
	SDL_DestroyTexture(m_pTexture);
}

void Gun::move()
{
	computeMouseDirection();
	m_changeDirection();
	float angleToMouse = Util::signedAngle(getCurrentDirection(),m_vMouseDirection);
	if (abs(angleToMouse)> 6.0f) {
		if (angleToMouse > 1.0f)
			turnRight();
		if (angleToMouse < -1.0f)
			turnLeft();
	}
	//setVelocity(getCurrentDirection());
	//setPosition(m_vPosition + getVelocity());
	
}

Gun::~Gun()
{
	
}
