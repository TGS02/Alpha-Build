#pragma once
#include "DataSet.h"
#include "Tile.h"

class TileMap
{
private:
	std::string m_strFileName;
	std::vector<DataSet_1D<Tile>> m_TileSet;
	unsigned int m_iGridSize[3];	// This array stores the sizes for each element of the vector - Layers, Rows, Columns
	unsigned int m_iTileSize[2];	// This array stores the base w and h values for tiles on the interactable layers.
	std::vector<Tile*> m_TileGrid;	// This vector stores Tile*s by [Layer * Row * Column]
	std::vector<BackgroundTile*> m_IntersectingTiles;	// This vector stores Tile*s that are intersecting with the player
	std::vector<StaticTile*> m_CollidingTiles;			// This vector stores Tile*s that are colliding with the player
	std::vector<StaticTile*> m_SupportingTiles;			// This vector stores Tile*s that are directly underneath the player
	std::vector<InteractiveTile*> m_InteractingTiles;	// This vector stores Tile*s that are interacting with the player
public:
	// System functions
	TileMap(std::string filename) : m_strFileName(filename) {}
	virtual bool LoadFromXML();
	void clean();
	void print();

	// Gameplay functions
	virtual void draw();
	virtual void checkCollision(SDL_Rect collider);
	virtual void checkIntersection(SDL_Rect collider);
	virtual void checkInteraction(SDL_Rect collider);
	//virtual InteractiveTile* findStartingTile();
	 InteractiveTile* findStartingTile();
	virtual void update();
	virtual void reset();

	// Mutator functions
	virtual void setFileName(std::string filename) { m_strFileName = filename; }

	// Accessor functions
	virtual const SDL_Rect getBounds();
	virtual const std::string getFileName() { return m_strFileName; }
	virtual DataSet_1D<Tile>* getTileSet(unsigned int index = 0) { return &m_TileSet[index]; }
	virtual Tile* getTile(unsigned int layer, unsigned int pos_x, unsigned int pos_y) {
		return m_TileGrid[layer * m_iGridSize[1] * m_iGridSize[2] + pos_y * m_iGridSize[2] + pos_x]; }
	virtual std::vector<BackgroundTile*>* getIntersectingTiles() { return &m_IntersectingTiles; }
	virtual std::vector<StaticTile*>* getCollidingTiles() { return &m_CollidingTiles; }
	virtual std::vector<StaticTile*>* getSupportingTiles() { return &m_SupportingTiles; }
	virtual std::vector<InteractiveTile*>* getInteractingTiles() { return &m_InteractingTiles; }
};
