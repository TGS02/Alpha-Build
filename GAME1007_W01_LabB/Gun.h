#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <glm\vec2.hpp>

class Gun
{
private:
	SDL_Texture* m_pTexture;
	glm::vec2 m_vPosition;
	glm::vec2 m_vMousePosition;
	SDL_Rect m_src, m_dst;
	
	SDL_RendererFlip flip;
	float m_speed;
	float m_turnRate;
	void m_changeDirection();
	float m_currentHeading;
	float angleToMouse;
	glm::vec2 m_VCurrentDirection;
	glm::vec2 m_vMouseDirection;
	glm::vec2 m_vVelocity;
	int delayMin, delayMax; // To create a delay after player dies.
	bool startFlashing;
	int flashMin, flashMax; // Player starts flashing after dying.
	int stopMin, stopMax; // Set total time for player to keep flashing.
	bool playerDie;
	int counterShoot;
	bool drawShoot;
	glm::vec2 recoilDrag;
public:
	Gun(glm::vec2);
	~Gun();
	bool left;
	void draw(SDL_Renderer* g_p_renderer);
	void shoot();
	void update();
	void clean();
	void move();
	void turnRight();
	void turnLeft();
	SDL_Texture* loadGun(SDL_Renderer*);
	//getters
	glm::vec2 getCurrentDirection();
	glm::vec2 getVelocity();
	float getMaxSpeed();
	glm::vec2 getMousePosition();
	bool getRotation();
	void getPlayerDie(bool m_hasDied);
	// setters
	void setVelocity(glm::vec2 newVelocity);
	void setCurrentDirection(glm::vec2 newDirection);
	void setPosition(glm::vec2 newPosition);
	glm::vec2 getPosition();
	void setMousePosition(glm::vec2 newPosition);
	void setRotation(bool newRot);
	void checkInMouseDirecion();
	void computeMouseDirection();
	void getShootFsm(bool shoot);
};

