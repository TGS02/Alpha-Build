#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <glm\vec2.hpp>
#include "Scorecard.h"
#include "TileMap.h"
#include "Weapon.h"
#include "Camera.h"
using namespace std;

struct Forces
{
	Forces() { Clear(); }
	float air_control;
	float grd_control;
	glm::vec2 air_force;
	glm::vec2 grd_force;
	float air_drag;
	float grd_drag;
	float air_maxSpeed;
	float grd_maxSpeed;
	float air_maxDrag;
	float grd_maxDrag;
	glm::vec2 jumpForce;
	float jumpForceMax;
	glm::vec2 jumpImpulse;
	unsigned int numSupportingTiles;
	void Clear();
	void Update(TileMap* tileMap);
};

class Player
{

private:
	int m_iDir; // Direction. -1 or 1. Not being used in this example.

	/********************************************/
	SDL_Texture* m_pTexture;
	//AmmoUI texture
	SDL_Texture* m_uTexture;

	int velX, velY;
	SDL_Rect m_src, m_dst, m_col;
	glm::vec2 m_pos;
	//ui ammo frame
	int frame = 0;
	SDL_Rect m_uis, m_uip;

	int m_frame,
		m_frameMax,
		m_sprite,
		m_spriteMax;
	const Uint8* g_iKeystates;
	bool left;
	int m_lastPosition;
	bool m_hasDied;
	int delayMin, delayMax; // To create a delay after player dies.
	bool startFlashing;
	int flashMin, flashMax; // Player starts flashing after dying.
	int stopMin, stopMax; // Set total time for player to keep flashing.
	InteractiveTile* m_pStartingTile;

	// Physics variables
	glm::vec2 m_fVelocity;
	glm::vec2 m_fAcceleration;
	bool onGround;
	bool isJumping;
	glm::vec2 m_fTotalJumpForce;
	TileMap* m_pTileMap;
	Forces m_forces;

	Weapon* m_pWeapon;
	glm::vec2 m_fRecoilVelocity;

public:
	int record;
	bool finish;
	bool stop;
	void Update();
	void Stop();
	void SetDir(int dir);
	bool IsGrounded();
	void SetGrounded(bool g);
	float getControl() { return m_forces.numSupportingTiles > 0 ? m_forces.grd_control : m_forces.air_control; }
	glm::vec2& getVelocity() { return m_fVelocity; }
	glm::vec2& getAcceleration() { return m_fAcceleration; }
	void SetX(int y);
	void SetY(int y);
	void SetLeft(bool l);
	bool GetLeft();

	/********************************************/
	Player();
	~Player();
	SDL_Texture* loadPlayer(SDL_Renderer*);
	SDL_Texture* loadAmmoUI(SDL_Renderer*);
	bool keyDown(SDL_Scancode);
	void playerUpdate();
	void setPosition(glm::vec2 position) { m_pos = position; }
	glm::vec2 getStartingPosition();
	void setStartingTile(InteractiveTile* startingTile) { m_pStartingTile = startingTile; }
	glm::vec2 getPosition() { return m_pos; }
	glm::vec2 getSize();
	SDL_Rect getCol() { return SDL_Rect{ m_dst.x + m_col.x, m_dst.y + m_col.y, m_col.w, m_col.h }; }
	SDL_FRect getFCol() { return SDL_FRect{ m_pos.x + (float)m_col.x, m_pos.y + (float)m_col.y, (float)m_col.w, (float)m_col.h }; }
	bool getRotation();
	bool getDie();
	void setRotation(bool newRot);
	void die();
	void jump(bool holdingKey = true);
	void shoot(glm::vec2 direction);
	void reload();
	Weapon* getWeapon() { return m_pWeapon; }
	void setWeapon(Weapon* weapon) { m_pWeapon = weapon; }
	void setTileMap(TileMap* tileMap) { m_pTileMap = tileMap; }
	void playerDraw(SDL_Renderer*);
	void animate();
	void accelerate();
	void move();
	void checkBound();
	void clean();
};

