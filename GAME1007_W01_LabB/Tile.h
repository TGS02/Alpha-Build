#pragma once
#include "SDL.h"
#include "glm/vec2.hpp"
#include <string>

/*SO! What does the tile need, what does the tileSET need? Right?
The Level loads both a TileSET and a TileMAP, both into memory.
The TileSET is loaded first.
The TileSET includes an array of various Tiles of different types (and the know-how to load and unload them).
The TileMAP includes various different layers of Tiles...
	0) Distance Layer
	1) Background Layer
	2) Static Layer
	3) Dynamic Layer
	4) Foreground Layer
	Each of which is, for now, the same height and width in terms of number of tiles, if not size of tiles
During gamplay:
	The 1st check is for INTERSECTION, which is checked against the BACKGROUND Layer
	The 2nd check is for DYNAMIC COLLISION, which is checked against the DYNAMIC Layer
	The 3rd check is for STATIC COLLISION, which is checked against the STATIC Layer
	For now, only the 1st and 3rd checks need to be implemented
Therefore, the TileSET needs to have tiles, at the least, for the background and static layers.
Ideally, the TileSets would all have an equal number of tiles all in equal positions, but we only have one set anyway
The TileSet, therefore, only contains the ability to load tiles from xml... it is a typical dataset
The TILES, however...
So... I have two options.
	In option 1, each tile has its own dst rectangle which can be called by accessing the tilemap index for that tile
	In option 2, the method for accessing is still the same, sorta... but the dst is generated on the fly by the tilemap
	the first would be easier, but more prone to possible errors.
	Lets go with the first for now.
In that case:
	ALL TILES NEED:
		a texture*
		a dst rect for their position in world coordinate space (can be int)
		a src rect for their position in texture space (must be int)
		an int for number of sprites in x axis
			alternatively, it could be a vector, allowing for mutliple animation states? later...
		an int for current sprite
		an int for frame to iterate on
		an int for current frame
	ALL BACKGROUND TILES NEED:
		float m_fDrag;			// Scalar which applies negatively every update (*frametime) to the player's current velocity, either as a multiplier, or as a vector in the reverse direction. This DOES NOT apply to any velocity gained from recoil.
		float m_fMaxSpeed;		// Scalar which defines the upper limit for the player's velocity, NOT COUNTING any velocity gained from recoil.
		float m_fMaxDrag;		// Scalar which functions the same as regular drag, but only while the player is exceeding the max speed.
		vec2 m_vForce;			// Vector which is added every update (*frametime) to the player's current velocity.
		vec2 m_vJumpForce;		// Vector which is added every update (*frametime) to the player's current velocity for as long as the player continues to hold the JUMP button up to the maximum.
		float m_fJumpForceMax;	// Scalar which defines the upper limit for ONLY the velocity the player gained from jumping. 
	ALL STATIC TILES NEED:
		ANOTHER dst rect for their collision in world coordinate space (can be int)
		float m_fDrag;			// Scalar which applies negatively every update (*frametime) to the player's current velocity, either as a multiplier, or as a vector in the reverse direction. This DOES NOT apply to any velocity gained from recoil.
		float m_fMaxSpeed;		// Scalar which defines the upper limit for the player's velocity, NOT COUNTING any velocity gained from recoil.
		float m_fMaxDrag;		// Scalar which functions the same as regular drag, but only while the player is exceeding the max speed.
		vec2 m_vForce;			// Vector which is added every update (*frametime) to the player's current velocity.
		vec2 m_vJumpImpulse;	// Vector which is added to the player's current velocity only on the exact frame that the player presses the JUMP button.

*/

class Tile
{
private:
	SDL_Texture* m_pTex;
	SDL_Rect m_irSrc;
	SDL_Rect m_irDst;
	unsigned short m_iSprite;
	unsigned short m_iSpriteMax;
	unsigned short m_iFrame;
	unsigned short m_iFrameMax;
public:
	// System functions
	Tile(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst, unsigned short sprite, unsigned short spriteMax, unsigned short frame, unsigned short frameMax)
		: m_pTex(tex), m_irSrc(src), m_irDst(dst), m_iSprite(sprite), m_iSpriteMax(spriteMax), m_iFrame(frame), m_iFrameMax(frameMax) {}
	~Tile() {}

	// Gameplay functions
	virtual void draw();
	virtual void update() {}

	// Mutator functions
	virtual void setTexture(SDL_Texture* tex) { m_pTex = tex; }
	virtual void setSrc(const SDL_Rect& ir) { m_irSrc = ir; }
	virtual void setDst(const SDL_Rect& ir) { m_irDst = ir; }
	virtual void setSprite(unsigned short i) { m_iSprite = i; }
	virtual void setSpriteMax(unsigned short i) { m_iSpriteMax = i; }
	virtual void setFrame(unsigned short i) { m_iFrame = i; }
	virtual void setFrameMax(unsigned short i) { m_iFrameMax = i; }

	// Accessor functions
	const SDL_Texture* getTexture() {return m_pTex; }
	const SDL_Rect& getSrc() { return m_irSrc; }
	const SDL_Rect& getDst() {return m_irDst; }
	const unsigned short getSprite() { return m_iSprite; }
	const unsigned short getSpriteMax() { return m_iSpriteMax; }
	const unsigned short getFrame() { return m_iFrame; }
	const unsigned short getFrameMax() { return m_iFrameMax; }
};

class WorldTile
	: public Tile
{
private:
	float m_fDrag;			// Scalar which applies negatively every update (*frametime) to the player's current velocity, either as a multiplier, or as a vector in the reverse direction. This DOES NOT apply to any velocity gained from recoil.
	float m_fMaxSpeed;		// Scalar which defines the upper limit for the player's velocity, NOT COUNTING any velocity gained from recoil.
	float m_fMaxDrag;		// Scalar which functions the same as regular drag, but only while the player is exceeding the max speed.
	glm::vec2 m_vForce;	// Vector which is added every update (*frametime) to the player's current velocity.
public:
	// System functions
	WorldTile(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst, unsigned short sprite, unsigned short spriteMax, unsigned short frame, unsigned short frameMax,
		float drag, float maxSpeed, float maxDrag, glm::vec2 force)
		: Tile(tex, src, dst, sprite, spriteMax, frame, frameMax), m_fDrag(drag), m_fMaxSpeed(maxSpeed), m_fMaxDrag(maxDrag), m_vForce(force) {}
	~WorldTile() {}

	// Gameplay functions

	// Mutator functions
	virtual void setDrag(float f) { m_fDrag = f; }
	virtual void setMaxSpeed(float f) { m_fMaxSpeed = f; }
	virtual void setMaxDrag(float f) { m_fMaxDrag = f; }
	virtual void setForce(glm::vec2 v) { m_vForce = v; }

	// Accessor functions
	virtual const float getDrag() { return m_fDrag; }
	virtual const float getMaxSpeed() { return m_fMaxSpeed; }
	virtual const float getMaxDrag() { return m_fMaxDrag; }
	virtual const glm::vec2& getForce() { return m_vForce; }
};

class BackgroundTile
	: public WorldTile
{
private:
	glm::vec2 m_vJumpForce;		// Vector which is added every update (*frametime) to the player's current velocity for as long as the player continues to hold the JUMP button up to the maximum.
	float m_fJumpForceMax;		// Scalar which defines the upper limit for ONLY the velocity the player gained from jumping. 
public:
	// System functions
	BackgroundTile(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst, unsigned short sprite , unsigned short spriteMax, unsigned short frame, unsigned short frameMax,
		float drag, float maxSpeed, float maxDrag, glm::vec2 force,
		glm::vec2 jumpForce, float jumpForceMax)
		: WorldTile(tex, src, dst, sprite, spriteMax, frame, frameMax, drag, maxSpeed, maxDrag, force),
		m_vJumpForce(jumpForce), m_fJumpForceMax(jumpForceMax) {}
	~BackgroundTile() {}
	
	// Gameplay functions

	// Mutator functions
	virtual void setJumpForce(glm::vec2 v) { m_vJumpForce = v; }
	virtual void setJumpForceMax(float f) { m_fJumpForceMax = f; }

	// Accessor functions
	virtual const glm::vec2& getJumpForce() { return m_vJumpForce; }
	virtual const float getJumpForceMax() { return m_fJumpForceMax; }
};

class StaticTile
	: public WorldTile
{
public:
	// Enumation
	enum class Type { IGNORE, SOLID, PLATFORM };
private:
	SDL_FRect m_frCol;			// SDL_Rect <int> which specifies the area against which the player can collide, as distinct from the area of the tile's image only for this type of tile.
	glm::vec2 m_vJumpImpulse;	// Vector which is added to the player's current velocity only on the exact frame that the player presses the JUMP button.
	Type m_Type;
public:
	// System functions
	StaticTile(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst, SDL_FRect& col, unsigned short sprite, unsigned short spriteMax, unsigned short frame, unsigned short frameMax,
		float drag, float maxSpeed, float maxDrag , glm::vec2 force,
		glm::vec2 jumpImpulse, Type type)
		: WorldTile(tex, src, dst, sprite, spriteMax, frame, frameMax, drag, maxSpeed, maxDrag, force),
		m_frCol(col), m_vJumpImpulse(jumpImpulse), m_Type(type) {}
	~StaticTile() {}

	// Gameplay functions

	// Mutator functions
	virtual void setCol(const SDL_FRect& ir) { m_frCol = ir; }
	virtual void setJumpImpulse(glm::vec2 v) { m_vJumpImpulse = v; }

	// Accessor functions
	virtual const SDL_Rect& getCol() { return SDL_Rect{ getDst().x + static_cast<int>(m_frCol.x), getDst().y + static_cast<int>(m_frCol.y), static_cast<int>(m_frCol.w), static_cast<int>(m_frCol.h) }; }
	virtual const glm::vec2& getJumpImpulse() { return m_vJumpImpulse; }
	virtual const Type getType() { return m_Type; }
};

class InteractiveTile
	: public Tile
{
public:
	// Enumation
	enum class Type { IGNORE, DIE, GET, WIN };
private:
	SDL_FRect m_frCol;				// SDL_Rect <int> which specifies the area against which the player can collide, as distinct from the area of the tile's image only for this type of tile.
	Type m_Type;
public:
	// System functions
	InteractiveTile(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dst, SDL_FRect& col, unsigned short sprite, unsigned short spriteMax, unsigned short frame, unsigned short frameMax,
		Type type)
		: Tile(tex, src, dst, sprite, spriteMax, frame, frameMax), m_frCol(col), m_Type(type) {}
	~InteractiveTile() {}

	// Gameplay functions

	// Mutator functions
	virtual void setCol(const SDL_FRect& ir) { m_frCol = ir; }

	// Accessor functions
	virtual const SDL_Rect& getCol() { return SDL_Rect{ getDst().x + static_cast<int>(m_frCol.x), getDst().y + static_cast<int>(m_frCol.y), static_cast<int>(m_frCol.w), static_cast<int>(m_frCol.h) }; }
	virtual const Type getType() { return m_Type; }
};