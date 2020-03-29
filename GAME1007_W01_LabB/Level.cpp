#include "tinyxml2.h"
#include "Level.h"
#include "GameData.h"

void Level::UnloadScorecardSet()
{
	//m_pScorecardSet
	//if (m_pScorecardSet != nullptr)
	//	delete[] m_pScorecardSet;
	//m_pScorecardSet = nullptr;
}

void Level::UnloadCoverImage()
{
	//if (m_pCoverImage != nullptr)
	//	delete m_pCoverImage;
	//m_pCoverImage = nullptr;
}

void Level::UnloadTileMap()
{
	//if (m_pTileMap != nullptr)
	//	delete m_pTileMap;
	//m_pTileMap = nullptr;
}

bool Level::LoadScorecardSet()
{
	printFileName("Level::LoadScorecardSet");
	//UnloadScorecardSet(); // Make sure the scorecard set is properly deleted if needed before it is loaded
	//for (unsigned int weaponIndex = 0; weaponIndex < GameData::getNumWeapons(); weaponIndex++)
	//{
	//	for (unsigned int collectibleIndex = 0; collectibleIndex < this->getNumCollectibles(); collectibleIndex++)
	//	{
	//		m_pScorecardSet[weaponIndex][collectibleIndex] = new Scorecard(GameData::getPlayerName(), static_cast<Weapon_Type>(weaponIndex + 1), m_iNumCollectibles);
	//		if (m_pScorecardSet[weaponIndex][collectibleIndex]->LoadFromXML() != 0)
	//			//return 1;
	//			;
	//	}
	//}
	return 0;
}

// Utility function to check if the cover image is in memory
bool Level::LoadCoverImage()
{
	// Make sure the cover image is properly deleted if needed before it is loaded

	//if (load)
	//{
	//	 Load from xml
	//}
	return false;
}

// Utility function to check if the tilemap is in memory
bool Level::LoadTileMap()
{
	// Make sure the tilemap is properly deleted if needed before it is loaded

	//if (load)
	//{
	//	 Load from xml
	//	 Also load tileh/w
	//}
	return false;
}

///*  Flags:
//0 = Load everything except the tileset.
//1 = Load only the cover image and unload the tileset.
//2 = Load only the tileset and unload the cover image.
//default = Load everything.*/
//void Level::LoadFromXML(unsigned char flags)
//{
//	//
//	// Load xml file with name: m_sFileName
//	//
//	switch (flags)
//	{
//	case 0:
//		m_iNumCollectibles = 1; // Load from xml
//		m_ActiveWeapon = Weapon_Type::None; // Load from xml
//		createScorecardSet();	// Load from xml
//		// Do not break;
//	case 1:
//		LoadCoverImage();
//		UnloadTileMap();
//		break;
//	case 2:
//		UnloadCoverImage();
//		LoadTileMap();
//		break;
//	default:
//		m_iNumCollectibles = 1; // Load from xml
//		m_ActiveWeapon = Weapon_Type::None; // Load from xml
//		createScorecardSet();	// Load from xml
//		LoadCoverImage();
//		LoadTileMap();
//	}
//}

// Loads all metadata for the level except the cover image
bool Level::LoadFromXML(DataSet::Flags unloadFlags, DataSet::Flags loadFlags)
{
	//std::cout << "Loading TileMap from XML." << std::endl;
	m_pTileMap = new TileMap(getFileName());
	return m_pTileMap->LoadFromXML() == true ? true : false;
}

void Level::Clean(DataSet::Flags flags)
{
	UnloadCoverImage();
	UnloadTileMap();
	UnloadScorecardSet();
}
