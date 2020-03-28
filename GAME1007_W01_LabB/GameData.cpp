#include <iostream>
#include "GameData.h"
#include "tinyxml2.h"

/*Current implementation doesn't care about flags,
doesn't care about the player's name,
doesn't unload anything,
and loads everything regardless.*/
bool GameData::LoadFromXML(GameData::Flags unloadFlags, GameData::Flags loadFlags)
{
	/* ---- ---- ---- ---- ---- Unload Anything ---- ---- ---- ---- ---- */
	if (unloadFlags != Flags::NONE)
	{
		Clean(Flags::ALL);
	}

	/* ---- ---- ---- ---- ---- Load Anything ---- ---- ---- ---- ---- */
	if (loadFlags != Flags::NONE)
	{
		// Create the XML document
		tinyxml2::XMLDocument xmlDoc;
		if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
		{
			std::cout << "GameData::LoadFromXML" << std::endl;
			xmlDoc.PrintError();
			return xmlDoc.Error();
		}

		// Define the temporary storage variables
		const char* ROOT = "gamedata";
		const char* ATTRIBUTE_ID = "id";
		const char* ATTRIBUTE_NAME = "name";
		const char* CHILD_WEAPONSET = "weaponset";
		const char* CHILD_LEVELSET = "levelset";
		tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
		tinyxml2::XMLElement* pElement[2];

		/* ---- ---- ---- ---- ---- Load PlayerDataSet ---- ---- ---- ---- ---- */
		if (loadFlags == Flags::ALL)
		{
			// Load the playerDataSet using its own internal loading function, since it references a completely different xml file.
			getPlayerDataSet()->LoadFromXML(DataSet::Flags::ALL, DataSet::Flags::FROMISTREAM);
			std::cout << "All " << m_pPlayerDataSet.getDataSet()->size() << " players' data loaded successfully." << std::endl;
		}

		/* ---- ---- ---- ---- ---- Load WeaponSetArray ---- ---- ---- ---- ---- */
		if (loadFlags == Flags::ALL) // Note that flags don't currently work, so this is the best I can do
		{
			// Populate each WeaponSet
			pElement[0] = pRoot->FirstChildElement(CHILD_WEAPONSET);
			unsigned int setId;
			while(pElement[0] != nullptr)
			{
				pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &setId);
				std::string name = pElement[0]->Attribute(ATTRIBUTE_NAME);
				m_pWeaponSetArray.push_back(new DataSet_1D<Weapon>(setId, name, TGS02_GAMEDATAFILE));
				m_pWeaponSetArray.back()->LoadFromXML();
				pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET);
			}
			std::cout << "All weapon data sets loaded successfully." << std::endl;
		}

		/* ---- ---- ---- ---- ---- Load LevelSetArray ---- ---- ---- ---- ---- */
		if (loadFlags == Flags::ALL) // Note that flags don't currently work, so this is the best I can do
		{
			// Populate each LevelSet
			pElement[0] = pRoot->FirstChildElement(CHILD_LEVELSET);
			for (unsigned int setId; pElement[0] != nullptr; setId++, pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET))
			{
				pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &setId);
				std::string name = pElement[0]->Attribute(ATTRIBUTE_NAME);
				m_pLevelSetArray.push_back(new DataSet_1D<Level>(setId, name, TGS02_GAMEDATAFILE));
				m_pLevelSetArray.back()->LoadFromXML();
			}
		}
		std::cout << "All game data loaded successfully." << std::endl;
	}
	return true;
}

// Current implementation can only clean everything
void GameData::Clean(Flags unloadFlags)
{
	/* ---- ---- ---- ---- ---- Unoad LevelSetArray ---- ---- ---- ---- ---- */
	if (unloadFlags == Flags::ALL)
	{
		for (unsigned int setId = 0; setId < m_pLevelSetArray.size(); setId++)
		{
			delete m_pLevelSetArray[setId];
			m_pLevelSetArray[setId] = nullptr;
		}
		m_pLevelSetArray.clear();
		m_pLevelSetArray.shrink_to_fit();
	}

	/* ---- ---- ---- ---- ---- Unload WeaponSetArray ---- ---- ---- ---- ---- */
	if (unloadFlags == Flags::ALL)
	{
		for (unsigned int setId = 0; setId < m_pWeaponSetArray.size(); setId++)
		{
			delete m_pWeaponSetArray[setId];
			m_pWeaponSetArray[setId] = nullptr;
		}
		m_pWeaponSetArray.clear();
		m_pWeaponSetArray.shrink_to_fit();
	}

	/* ---- ---- ---- ---- ---- Unload PlayerDataSet ---- ---- ---- ---- ---- */
	if (unloadFlags == Flags::ALL)
	{
		m_pPlayerDataSet.Clean();
	}
}

GameData* GameData::Instance()
{
	static GameData* instance = new GameData(); // Instance either created or referenced.
	return instance;
}
