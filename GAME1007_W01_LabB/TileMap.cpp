#include <iostream>
#include <iomanip>
#include "TileMap.h"
#include "tinyxml2.h"
#include "Engine.h"
using namespace tinyxml2;

bool TileMap::LoadFromXML()
{
	// Create the XML document
	XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
	{
		xmlDoc.PrintError();
		return xmlDoc.Error();
	}
	
	// Define the tags and temporary storage variables
	const char* ROOT = "map";
	const char* ATTRIBUTE_ID = "id";
	const char* ATTRIBUTE_NAME = "name";
	const char* ATTRIBUTE_SOURCE = "source";
	const char* ATTRIBUTE_WIDTH = "width";
	const char* ATTRIBUTE_HEIGHT = "height";
	const char* ATTRIBUTE_TILEWIDTH = "tilewidth";
	const char* ATTRIBUTE_TILEHEIGHT = "tileheight";
	const char* ATTRIBUTE_NEXTLAYERID = "nextlayerid";
	const char* CHILD_TILESET = "tileset";
	const char* ATTRIBUTE_FIRSTGID = "firstgid";
	const char* CHILD_PROPERTIES = "properties";
	const char* PROPERTY_COLLECTIBLES = "Collectibles";
	const char* PROPERTY_COVERIMAGE = "CoverImage";
	const char* PROPERTY_UNLOCKCODE = "UnlockCode";
	const char* CHILD_LAYER = "layer";
	const char* CHILD_DATA = "data";
	const char* CHILD_TILE = "tile";
	const char* ATTRIBUTE_GID = "gid";
	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
	tinyxml2::XMLElement* pElement[2];
	unsigned int id[2];
	std::string filename;

	// Parse the outer level data
	pElement[0] = xmlDoc.FirstChildElement(ROOT);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_WIDTH, &m_iGridSize[2]);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_HEIGHT, &m_iGridSize[1]);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_TILEWIDTH, &m_iTileSize[0]);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_TILEHEIGHT, &m_iTileSize[1]);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_NEXTLAYERID, &m_iGridSize[0]);
	m_iGridSize[0]--;

	// Generate the array
	m_TileGrid.reserve(m_iGridSize[0] * m_iGridSize[1] * m_iGridSize[2]);

	/* ---- ---- ---- ---- ---- ---- ---- TileSet loadFromXML ---- ---- ---- ---- ---- ---- ---- */
	// Load the TileSet
	for (pElement[0] = pRoot->FirstChildElement(CHILD_TILESET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_TILESET))
	{
		pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_FIRSTGID, &id[0]);
		filename = pElement[0]->Attribute(ATTRIBUTE_SOURCE);
		filename = "GameData/" + filename;	// Make sure it's looking in the right directory
		m_TileSet.push_back(DataSet_1D<Tile>(id[0], filename, filename));
		m_TileSet.back().LoadFromXML();
	}

	/* ---- ---- ---- ---- ---- ---- ---- TileMap loadFromXML ---- ---- ---- ---- ---- ---- ---- */
	// Iterate through the layers (CHILD_LAYER)
	for (pElement[0] = pRoot->FirstChildElement(CHILD_LAYER);
		pElement[0] != nullptr;
		pElement[0] = pElement[0]->NextSiblingElement(CHILD_LAYER))
	{
		// Iterate through the tiles (CHILD_TILE)
		int position_x = -1;
		int position_y = -1;
		for (pElement[1] = pElement[0]->FirstChildElement(CHILD_DATA)->FirstChildElement(CHILD_TILE);
			pElement[1] != nullptr;
			pElement[1] = pElement[1]->NextSiblingElement(CHILD_TILE))
		{
			position_x++;
			if (position_x % 32 == 0)
			{
				position_x = 0;
				position_y++;
			}

			if (pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_GID, &id[1]) == XML_NO_ATTRIBUTE)
				id[1] = 1; // Make sure there's an int to push back, even if it's 0.
			// Determine the appropriate Tile to push into the vector
			Tile* tileFromSet = m_TileSet[0].getDatum(id[1] - 1);	// Can only load from one TileSet for now.

			if (dynamic_cast<BackgroundTile*>(tileFromSet) != nullptr)
				m_TileGrid.push_back(new BackgroundTile(*dynamic_cast<BackgroundTile*>(tileFromSet)));
			if (dynamic_cast<StaticTile*>(tileFromSet) != nullptr)
				m_TileGrid.push_back(new StaticTile(*dynamic_cast<StaticTile*>(tileFromSet)));
			if (dynamic_cast<InteractiveTile*>(tileFromSet) != nullptr)
				m_TileGrid.push_back(new InteractiveTile(*dynamic_cast<InteractiveTile*>(tileFromSet)));
			unsigned int gridpos = m_TileGrid.size() % (m_iGridSize[1] * m_iGridSize[2]); // Account for the layer
			m_TileGrid.back()->setDst(SDL_Rect{
				//static_cast<int>((gridpos % m_iGridSize[2]) * m_iTileSize[0]), // To get x, % xsize and * width
				//static_cast<int>((gridpos / m_iGridSize[1]) * m_iTileSize[1]), // To get y, / xsize and * height
				position_x * static_cast<int>(m_iTileSize[0]),
				position_y * static_cast<int>(m_iTileSize[1]),
				m_TileGrid.back()->getDst().w,
				m_TileGrid.back()->getDst().h});
		}
	}
	return true;
}

void TileMap::clean()
{
	// Since neither of the vectors contain dynamically allocated elements, there's no need to use delete
	m_TileGrid.clear();
	m_TileGrid.shrink_to_fit();
	m_TileSet.clear();
	m_TileSet.shrink_to_fit();
}

void TileMap::print()
{
	std::cout << "Printing TileMap with " << m_iGridSize[0] << " layers, " << m_iGridSize[1] << " rows, and " << m_iGridSize[2] << " columns." << std::endl;
	//for (unsigned int layerId = 0; layerId < m_iGridSize[0]; layerId++)
	//{
	//	std::cout << "Layer: " << layerId << " firstgid: " << m_TileSet[0].getId() << std::endl;
	//	for (unsigned int height = 0; height < m_iGridSize[1]; height++)
	//	{
	//		for (unsigned int width = 0; width < m_iGridSize[2]; width++)
	//		{
	//			int type;
	//			if (dynamic_cast<BackgroundTile*>(getTile(layerId, width, height)))
	//				type = 1;
	//			if (dynamic_cast<StaticTile*>(getTile(layerId, width, height)))
	//				type = 2;
	//			if (dynamic_cast<InteractiveTile*>(getTile(layerId, width, height)))
	//				type = 3;
	//			std::cout << type << ' ';
	//			//std::cout << std::setw(2) << getTile(layerId, width, height)->getDst().x << '-';
	//			//std::cout << std::setw(2) << getTile(layerId, width, height)->getDst().y << ' ';
	//			//std::cout << (layerId * m_iGridSize[1] * m_iGridSize[2]) + (height * m_iGridSize[2]) + (width) << ' ';
	//		}
	//		std::cout << std::endl;
	//	}
	//	std::cout << std::endl;
	//}

	for (unsigned int tileIndex = 0; tileIndex < m_TileGrid.size(); tileIndex++)
	{
		int type = 0;
		if (dynamic_cast<BackgroundTile*>(m_TileGrid[tileIndex]))
			type = 1;
		else if (dynamic_cast<StaticTile*>(m_TileGrid[tileIndex]))
			type = 2;
		else if (dynamic_cast<InteractiveTile*>(m_TileGrid[tileIndex]))
			type = 3;
		std::cout << type << ' ';
	}
}

void TileMap::draw()
{
	for (unsigned int tileIndex = 0; tileIndex < m_TileGrid.size(); tileIndex++)
	{
		m_TileGrid[tileIndex]->draw();
	}
}

void TileMap::checkCollision()
{
	// Clear the collision vectors for refilling
	m_IntersectingTiles.clear();
	m_IntersectingTiles.shrink_to_fit();
	m_CollidingTiles.clear();
	m_CollidingTiles.shrink_to_fit();
	m_InteractingTiles.clear();
	m_InteractingTiles.shrink_to_fit();

	// Obtain the player's dimensions
	GameState* gameState = dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetState().back());
	if (gameState != nullptr)
	{
		SDL_Rect playerCol = {
		gameState->getPlayer()->getPosition().x + 5,
		gameState->getPlayer()->getPosition().y,
		gameState->getPlayer()->getSize().x / 2,
		gameState->getPlayer()->getSize().y };

		// Iterate through all tiles
		for (unsigned int tileIndex = 0; tileIndex < m_TileGrid.size(); tileIndex++)
		{
			// Check for intersecting tiles
			BackgroundTile* intTile = dynamic_cast<BackgroundTile*>(m_TileGrid[tileIndex]);
			if (intTile != nullptr)
			{
				if (SDL_HasIntersection(&playerCol, &intTile->getDst()))
				{
					m_IntersectingTiles.push_back(intTile);
				}
			}

			// Check for colliding tiles
			StaticTile* colTile = dynamic_cast<StaticTile*>(m_TileGrid[tileIndex]);
			if (colTile != nullptr)
			{
				// Convert the col FRect to a regular IRect since SDL_HasIntersection demands it.
				if (SDL_HasIntersection(&playerCol, &colTile->getCol()))
				{
					m_CollidingTiles.push_back(colTile);
				}
			}

			// Check for interacting tiles
			InteractiveTile* actTile = dynamic_cast<InteractiveTile*>(m_TileGrid[tileIndex]);
			if (actTile != nullptr)
			{
				if (SDL_HasIntersection(&playerCol, &actTile->getCol()))
				{
					m_InteractingTiles.push_back(actTile);
				}
			}
		}
	}
}

void TileMap::update()
{
	for (unsigned int tileIndex = 0; tileIndex < m_TileGrid.size(); tileIndex++)
	{
		m_TileGrid[tileIndex]->update();
	}
}
