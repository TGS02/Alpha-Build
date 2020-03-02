#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "Map.h"
#include <glm\vec2.hpp>
using namespace std;


class Player
{

private:

	double m_dAccelX,
		m_dMaxAccelX,
		m_dAccelY,
		m_dVelX,
		m_dMaxVelX,
		m_dVelY,
		m_dMaxVelY,
		m_dDrag,
		m_dGrav;
	int m_iDir; // Direction. -1 or 1. Not being used in this example.

	/********************************************/
	SDL_Texture* m_pTexture;
	int m_iSpeed;
	int velX, velY;
	SDL_Rect m_src, m_dst;
	int m_frame, 
		m_frameMax, 
		m_sprite, 
		m_spriteMax; 
	const Uint8* g_iKeystates;
	bool left;
	bool onGround;
	int m_lastPosition;
	float jumpVel ;
	bool  jumping;
    float gravity ;
	bool die;
	int delayMin, delayMax; // To create a delay after player dies.
	bool startFlashing;
	int flashMin, flashMax; // Player starts flashing after dying.
	int stopMin, stopMax; // Set total time for player to keep flashing.
	

public:
	bool score;
	int record;
	bool finish;
	bool stop;
	void Update();
	void MoveX();
	void Stop();
	void SetDir(int dir);
	void SetAccelX(double a);
	void SetAccelY(double a);
	bool IsGrounded();
	void SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void SetVelX(double v);
	void setVelXMax(double v);
	void setVelyMax(double v);
	void setDrag(double d);
	void SetVelY(double v);
	void SetX(int y);
	void SetY(int y);
	void SetLeft(bool l);
	bool GetLeft();

	/********************************************/
	Player();
	~Player();
	SDL_Texture* loadPlayer(SDL_Renderer*);
	bool keyDown(SDL_Scancode);
	void playerUpdate(Map* map, Uint32 delta);
	glm::vec2 getPosition();
	glm::vec2 getSize();
	bool getRotation();
	bool getDie();
	void setRotation(bool newRot);
	void jump();
	void playerDraw(SDL_Renderer*);
	void animate();
	void checkCollision(int x, int y, Map* map);
	void checkBound();
	void clean();
};

