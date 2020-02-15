#include "Gun.h"
#include "TextureManager.h"
#include "Util.h"
#include <glm/vec2.hpp>
#include <ostream>
#include <iostream>

void Gun::m_changeDirection()
{
	float x = cos(m_currentHeading * Util::Deg2Rad);
	float y = sin(m_currentHeading * Util::Deg2Rad);
	m_VCurrentDirection = glm::vec2(x, y);

}


Gun::Gun(glm::vec2 playerPos)
{
	m_vPosition = playerPos;
	m_src = { 0,0,44,16 };
	left = false;
	m_turnRate = 20.0f; // 20 degrees per frame
	m_currentHeading = 0.0; //current facing angle
	m_VCurrentDirection = glm::vec2(1.0f, 0.0f);
	m_vVelocity = glm::vec2(0.0f, 0.0f);
	m_speed = 1;
	angleToMouse = 0;
}

SDL_Texture* Gun::loadGun(SDL_Renderer* m_pRenderer)
{
	
	m_pTexture = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/PPSH.png");
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
	velocity.x = getMousePosition().x - static_cast<int>(m_vPosition.x);
	velocity.y = getMousePosition().y - static_cast<int>( m_vPosition.y);
	m_vMouseDirection = Util::normalize(velocity);
	
}

glm::vec2 Gun::getMousePosition()
{
	return  m_vMousePosition;
}

bool Gun::getRotation()
{
	return left;
}

glm::vec2 Gun::getCurrentDirection()
{
	return m_VCurrentDirection;
}


void Gun::setPosition(glm::vec2 newPosition)
{
	m_vPosition = newPosition;
}

void Gun::setVelocity(glm::vec2 newVelocity)
{
	m_vVelocity = newVelocity;
}

void Gun::turnRight()
{
	float angleDifference = abs(m_turnRate - abs(angleToMouse)) * 0.2f;
	if (angleDifference < 0.25f) angleDifference = 0.0f;
	//std::cout << "Angle Diff:  " << angleDifference << std::endl;
	m_currentHeading += ((angleDifference < m_turnRate) ? angleDifference : m_turnRate) * m_speed;
	//m_currentHeading += m_turnRate*m_speed;

}
void Gun::turnLeft()
{
	float angleDifference = abs(m_turnRate - abs(angleToMouse)) * 0.2f;
	if (angleDifference < 0.25f) angleDifference = 0.0f;
	//std::cout << "Angle Diff:  " << angleDifference << std::endl;
	m_currentHeading -= ((angleDifference < m_turnRate) ? angleDifference : m_turnRate) * m_speed;

	//  m_currentHeading -= m_turnRate* m_speed;
}

void Gun::draw(SDL_Renderer* g_p_renderer)
{
	m_dst = { static_cast<int>(m_vPosition.x), static_cast<int>(m_vPosition.y) , 44, 10 };
	SDL_Point centerPoint = { 0, 5};
	if(!left)
	TextureManager::draw(g_p_renderer, m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_NONE);
	else {
		TextureManager::draw(g_p_renderer, m_pTexture, &m_src, &m_dst, m_currentHeading, 255, &centerPoint, SDL_FLIP_VERTICAL);
	}
}

void Gun::update()
{
	move();
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
	//std::cout << "angle to mouse"<< angleToMouse<< endl; 
	if (angleToMouse > 0.0f)
		turnRight();
	if (angleToMouse < 0.0f)
		turnLeft();
	//setVelocity(getCurrentDirection());
	//setPosition(m_vPosition + getVelocity());
	
}

Gun::~Gun()
{
	
}
