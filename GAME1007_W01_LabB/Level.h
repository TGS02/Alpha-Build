#pragma once
#include "SDL.h"
#include "Scorecard.h"
#include "TileMap.h"
#include "DataSet.h"

// Class for holding all surface data and necessary links for a given level
class Level
	: public DataSet
{
private:
	std::string m_strCoverImageFileName;
	std::string m_strUnlockCode;
	unsigned int m_iNumCollectables;
	//SDL_Texture* m_pCoverImage;		// Should be deallocated when inside the level
	TileMap* m_pTileMap;				// Should be deallocated when inside the main menu

	// Private system functions
	virtual void UnloadScorecardSet();
	virtual void UnloadCoverImage();
	virtual void UnloadTileMap();
	virtual bool LoadScorecardSet();
	virtual bool LoadCoverImage();
	virtual bool LoadTileMap();

	// Private mutator functions
	//virtual void setCoverImage(SDL_Texture* image) { m_pCoverImage = image; }
	virtual void setUnlockCode(std::string code) { m_strUnlockCode = code; }
	virtual void setNumCollectibles(unsigned int num) { m_iNumCollectables = num; }
public:
	// System functions
	Level(unsigned int id, std::string tilemapfile, std::string name, std::string coverimagefile, std::string unlockcode, unsigned int collectibles) : 
		DataSet(id, tilemapfile, name), m_strCoverImageFileName(coverimagefile), m_strUnlockCode(unlockcode), m_iNumCollectables(collectibles), m_pTileMap(nullptr) {}
	~Level() { Clean(); }
	virtual bool LoadFromXML(Flags unloadFlags = Flags::ALL, Flags loadFlags = Flags::ALL);
	virtual void Clean(Flags flags = Flags::ALL);

	// Accessor functions
	virtual std::string getUnlockCode() { return m_strUnlockCode; }
	virtual unsigned int getNumCollectables() { return m_iNumCollectables; }
	//virtual SDL_Texture* getCoverImage() { return m_pCoverImage; }
	virtual TileMap* getTileMap() { return m_pTileMap; }
};
