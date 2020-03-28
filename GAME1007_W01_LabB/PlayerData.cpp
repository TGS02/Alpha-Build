#include <vector>
#include "tinyxml2.h"
#include "PlayerData.h"
#include "GameData.h"

bool PlayerData::LoadFromXML()
{
	std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " loading started." << std::endl;

	/* ---- ---- ---- ---- ---- Load Anything ---- ---- ---- ---- ---- */
	//if (loadFlags != PlayerData::Flags::NONE)
	{
		// Create the XML document
		tinyxml2::XMLDocument xmlDoc;
		if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
		{
			xmlDoc.PrintError();
			return xmlDoc.Error();
		}

		// Define the temporary storage variables
		const char* csctr;
		std::string sctr;
		unsigned int ictr[6];
		bool bctr;
		std::string input = "";
		const char* ROOT = "playerdata";
		const char* ROOT_NAME = "name";
		const char* ROOT_NUMCOLLECTED = "numcollected";
		const char* ROOT_BODYFILE = "bodyfilename";
		const char* ROOT_ARMFILE = "armfilename";
		const char* ROOT_ACTIVEWEAPONSET = "activeweaponset";
		const char* ROOT_ACTIVELEVELSET = "activelevelset";
		const char* ID = "id";
		const char* WEAPONID = "weaponid";
		const char* UNLOCKED = "unlocked";
		const char* CHILD_ACTIVEWEAPON = "activeweapon";
		const char* CHILD_WEAPONSET = "weaponset";
		const char* CHILD_WEAPON = "weapon";
		const char* CHILD_LEVELSET = "levelset";
		const char* CHILD_LEVEL = "level";
		const char* CHILD_UNLOCKEDWEAPONS = "unlockedweapons";
		const char* CHILD_UNLOCKEDLEVELS = "unlockedlevels";
		const char* CHILD_SCORECARDDATA = "scorecarddata";
		const char* CHILD_COLLECTIBLE = "collectible";
		tinyxml2::XMLElement* pElement[5] = { nullptr };

		/* ---- ---- ---- ---- ---- Load PlayerData ---- ---- ---- ---- ---- */
		// Iterate through the root attributes
		pElement[0] = xmlDoc.FirstChildElement(ROOT);
		pElement[0]->QueryStringAttribute(ROOT_NAME, &csctr);
		setName(csctr);
		pElement[0]->QueryUnsignedAttribute(ROOT_NUMCOLLECTED, &ictr[0]);
		setNumCollected(ictr[0]);
		pElement[0]->QueryStringAttribute(ROOT_BODYFILE, &csctr);
		setBodyTextureFileName(csctr);
		pElement[0]->QueryStringAttribute(ROOT_ARMFILE, &csctr);
		setArmTextureFileName(csctr);
		pElement[0]->QueryUnsignedAttribute(ROOT_ACTIVEWEAPONSET, &ictr[0]);
		setActiveWeaponSet(ictr[0]);
		pElement[0]->QueryUnsignedAttribute(ROOT_ACTIVELEVELSET, &ictr[0]);
		setActiveLevelSet(ictr[0]);
		pElement[0] = nullptr;

		/* ---- ---- ---- ---- ---- Load PlayerData ActiveWeapon ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_ACTIVEWEAPON);

		// Iterate through the weaponsets (CHILD_WEAPONSET)
		for (unsigned int weaponSetId = 0; weaponSetId < GameData::Instance()->getWeaponSetArray()->size(); weaponSetId++)
		{
			if (pElement[0] == nullptr)
			{
				// set everything to zero.
			}
			else
			{
				pElement[0] = pElement[0]->FirstChildElement(CHILD_WEAPONSET);

				// Iterate through the levelsets (CHILD_LEVELSET)
				pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]); // Identify the WeaponSet to iterate through
				m_iActiveWeapon.push_back(new std::vector<std::vector<unsigned int>*>); // Push a new WeaponSet
				for (pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVELSET); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVELSET))
				{
					// Iterate through the levels (CHILD_LEVEL)
					pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]); // Identify the LevelSet to iterate through
					m_iActiveWeapon[ictr[0] - 1]->push_back(new std::vector<unsigned int>); // Push a new LevelSet
					for (pElement[2] = pElement[1]->FirstChildElement(CHILD_LEVEL); pElement[1] != nullptr; pElement[2] = pElement[2]->NextSiblingElement(CHILD_LEVEL))
					{
						// Read the level attributes
						pElement[2]->QueryUnsignedAttribute(ID, &ictr[2]);
						pElement[2]->QueryUnsignedAttribute(WEAPONID, &ictr[3]);
						m_iActiveWeapon[ictr[0] - 1]->at(ictr[1] - 1)->push_back(ictr[2]); // Push a specific Level
						setActiveWeapon(ictr[0] - 1, ictr[1] - 1, ictr[2] - 1, ictr[3]);
					}
					pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVELSET);
				}
			}
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "Active weapons for each level loaded succssfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData UnlockedWeapons ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_UNLOCKEDWEAPONS);

		// Iterate through the weaponsets (CHILD_WEAPONSET)
		for (pElement[0] = pElement[0]->FirstChildElement(CHILD_WEAPONSET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET))
		{
			m_bUnlockedWeapons.push_back(new std::vector<bool>);
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]);
			pElement[0]->QueryBoolAttribute(UNLOCKED, &bctr);
			setUnlockedWeaponSet(ictr[0], bctr);

			// Iterate through the weapons (CHILD_WEAPON)
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_WEAPON); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_WEAPON))
			{
				m_bUnlockedWeapons[ictr[0]]->push_back(new bool());
				// Read the weapon attributes 
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]);
				pElement[1]->QueryBoolAttribute(UNLOCKED, &bctr);
				setUnlockedWeapon(ictr[0], ictr[1], bctr);
				pElement[1] = pElement[1]->NextSiblingElement(CHILD_WEAPON);
			}
			pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET);
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "Unlocked weapons loaded successfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData UnlockedLevels ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_UNLOCKEDLEVELS);

		// Iterate through the levelsets (CHILD_LEVELSET)
		for (pElement[0] = pElement[0]->FirstChildElement(CHILD_LEVELSET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET))
		{
			// Push the vectors with the levelSet
			m_bUnlockedLevels.push_back(new std::vector<bool>);
			m_bCollectibleList.push_back(new std::vector<std::vector<bool>*>);
			
			// Set the Unlocked Level Set
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]);
			pElement[0]->QueryBoolAttribute(UNLOCKED, &bctr);
			setUnlockedLevelSet(ictr[0], bctr);

			// Iterate through the levels (CHILD_LEVEL)
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVEL); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVEL))
			{
				// Push the vectors with the level
				m_bUnlockedLevels[ictr[0]]->push_back(new bool);
				m_bCollectibleList[ictr[0]]->push_back(new std::vector<bool>);

				// Read the level attributes
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]);
				pElement[1]->QueryBoolAttribute(UNLOCKED, &bctr);
				setUnlockedLevel(ictr[0], ictr[1], bctr);

				// Iterate through the collectibles (CHILD_COLLECTIBLE)
				for (unsigned int index = 0; index < ictr[2]; index++)
				{
					m_bCollectibleList[ictr[0]]->at(ictr[1])->push_back(new bool);
					setCollectible(ictr[0], ictr[1], ictr[3], false);
				}

				pElement[2] = pElement[1]->FirstChildElement(CHILD_COLLECTIBLE);
				for (unsigned int index = 0; index < ictr[2]; index++)
				{
					// Read the collectible unlocked attributes only
					pElement[2]->QueryUnsignedAttribute(ID, &ictr[3]);
					pElement[2]->QueryBoolAttribute(UNLOCKED, &bctr);
					setCollectible(ictr[0], ictr[1], ictr[3], bctr);
					pElement[2] = pElement[2]->NextSiblingElement(CHILD_COLLECTIBLE);
				}
				pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVEL);
			}
			pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET);
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "Unlocked levels loaded successfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData ScoreCardData ---- ---- ---- ---- ---- */
		// Iterate through the weaponsets (CHILD_WEAPONSET)
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_SCORECARDDATA);
		for (unsigned int weaponSetId = 0; pElement[0] != nullptr; weaponSetId++, pElement[0]->NextSiblingElement(CHILD_WEAPONSET))
		{
			m_pScorecardSetArray.push_back(new std::vector<std::vector<DataSet_2D<Scorecard>*>*>);

			// Iterate through the levelsets (CHILD_LEVELSET)
			pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVELSET);
			for (unsigned int levelSetId = 0; pElement[1] != nullptr; levelSetId++, pElement[1]->NextSiblingElement(CHILD_LEVELSET))
			{
				m_pScorecardSetArray[weaponSetId]->push_back(new std::vector<DataSet_2D<Scorecard>*>);

				// Iterate through the levels (CHILD_LEVEL)
				pElement[2] = pElement[1]->FirstChildElement(CHILD_LEVEL);
				for (unsigned int levelId = 0; pElement[2] != nullptr; levelId++, pElement[2]->NextSiblingElement(CHILD_LEVEL))
				{
					std::string name = "ScorecardSet " + weaponSetId + '.' + levelSetId + '.' + levelId;
					m_pScorecardSetArray[weaponSetId]->at(levelSetId)->push_back(new DataSet_2D<Scorecard>(weaponSetId, levelSetId, levelId, name, getFileName()));
					m_pScorecardSetArray[weaponSetId]->at(levelSetId)->back()->LoadFromXML();
				}
				std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "All scorecard sets for level set " << levelSetId << " for " << weaponSetId << " loaded successfully." << std::endl;
			}
			std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "All scorecard sets for all level sets for weapon set " << weaponSetId << " loaded successfully." << std::endl;
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << "All scorecards loaded successfully." << std::endl;
	}
	std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " loaded successfully." << std::endl;
	return true;
}

bool PlayerData::SaveToXML()
{
	return false;
}

void PlayerData::Clean()
{
}

void PlayerData::printScorecardSetArray()
{
	const std::string _NumberOf = "Number of ";
	const std::string _ScordcardSetArray = "Scorecard Set Array: ";
	const std::string _WeaponSet = "Weapon Set";
	const std::string _LevelSet = "Level Set";
	const std::string _Level = "Level";

	std::cout << _ScordcardSetArray << ": " << _NumberOf << _WeaponSet << "s: " << GameData::Instance()->getWeaponSetArray()->size() << std::endl;
	for (unsigned int weaponSetId = 0; weaponSetId < GameData::Instance()->getWeaponSetArray()->size(); weaponSetId++)
	{
		std::cout << _WeaponSet << ": " << weaponSetId << ": " << _NumberOf << _LevelSet << "s: " << GameData::Instance()->getLevelSetArray()->size() << std::endl;
		for (unsigned int levelSetId = 0; levelSetId < GameData::Instance()->getLevelSetArray()->size(); levelSetId++)
		{
			std::cout << _LevelSet << ": " << levelSetId << ": " << _NumberOf << _Level << "s: " << GameData::Instance()->getLevelSetArray()->at(levelSetId)->getDataSet()->size() << std::endl;
			for (unsigned int levelId = 0; levelId < GameData::Instance()->getLevelSetArray()->at(levelSetId)->getDataSet()->size(); levelId++)
			{
				std::cout << _Level << ": " << levelId << ": " << std::endl;
				getScorecardSet(weaponSetId, levelSetId, levelId)->Print();
			}
		}
	}
}
