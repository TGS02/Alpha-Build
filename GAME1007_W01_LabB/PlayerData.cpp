#include <vector>
#include "tinyxml2.h"
#include "PlayerData.h"
#include "GameData.h"

PlayerData::PlayerData(std::string name) : m_strName(name),
	m_strBodyTextureFileName(""), m_strArmTextureFileName(""), m_iNumCollected(0), m_iNumSpent(0),
	m_iActiveWeaponSet(0), m_iActiveLevelSet(0)
{
	std::cout << "New PlayerData object " << m_strName << " has been created" << std::endl;

	// Fill the various active and unlocked vectors with default values (zeroes and falses)
	// Actives
	m_iActiveLevel.resize(GameData::Instance()->getLevelSetArray()->size());													// Number of LevelSets
	m_iActiveWeapon.resize(GameData::Instance()->getWeaponSetArray()->size());													// Number of WeaponSets

	// Unlocked weapons
	for (unsigned int weaponset = 0; weaponset < GameData::Instance()->getWeaponSetArray()->size(); weaponset++)				// Number of WeaponSets
	{
		m_iActiveWeapon[weaponset].resize(GameData::Instance()->getWeaponSet(weaponset)->getDataSet()->size());					// Number of Weapons in each set
		for (unsigned int levelset = 0; levelset < GameData::Instance()->getLevelSetArray()->size(); levelset++)				// Number of LevelSets
			m_iActiveWeapon[weaponset][levelset].resize(GameData::Instance()->getLevelSet(levelset)->getDataSet()->size());		// Number of Levels in each set
	}
	m_bUnlockedWeaponSets.resize(GameData::Instance()->getWeaponSetArray()->size());											// Number of WeaponSets
	m_bUnlockedWeapons.resize(GameData::Instance()->getWeaponSetArray()->size());												// Number of WeaponSets
	for (unsigned int i = 0; i < m_bUnlockedWeapons.size(); i++)
		m_bUnlockedWeapons[i].resize(GameData::Instance()->getWeaponSet(i)->getDataSet()->size());								// Number of Weapons in each set
	
	// Unlocked levels
	m_bUnlockedLevelSets.resize(GameData::Instance()->getLevelSetArray()->size());												// Number of LevelSets
	m_bUnlockedLevels.resize(GameData::Instance()->getLevelSetArray()->size());													// Number of LevelSets
	for (unsigned int i = 0; i < m_bUnlockedLevels.size(); i++)
		m_bUnlockedLevels[i].resize(GameData::Instance()->getLevelSet(i)->getDataSet()->size());								// Number of Levels in each set
	
	// Unlocked collectibles
	m_bCollectibleList.resize(GameData::Instance()->getLevelSetArray()->size());												// Number of LevelSets
	for (unsigned int levelset = 0; levelset < GameData::Instance()->getLevelSetArray()->size(); levelset++)					// Number of LevelSets
	{
		m_bCollectibleList[levelset].resize(GameData::Instance()->getLevelSet(levelset)->getDataSet()->size());					// Number of Levels in each set
		for (unsigned int level = 0; level < GameData::Instance()->getLevelSet(levelset)->getDataSet()->size(); level++)		// Number of Levels in each set
			m_bCollectibleList[levelset][level].resize(GameData::Instance()->getLevelSet(levelset)->getDatum(level)->getNumCollectables());	// Number of Collectibles in each level
	}

	// Scorecards
	m_pScorecardArray.resize(GameData::Instance()->getLevelSetArray()->size());											// Number of LevelSets
	for (unsigned int levelset = 0; levelset < GameData::Instance()->getLevelSetArray()->size(); levelset++)				// Number of LevelSets
	{
		m_pScorecardArray[levelset].resize(GameData::Instance()->getLevelSet(levelset)->getDataSet()->size());			// Number of Levels in each set
		for (unsigned int level = 0; level < GameData::Instance()->getLevelSet(levelset)->getDataSet()->size(); level++)	// Number of Levels in each set
		{
			m_pScorecardArray[levelset][level].resize(GameData::Instance()->getWeaponSetArray()->size());				// Number of WeaponSets
			for (unsigned int weaponset = 0; weaponset < GameData::Instance()->getWeaponSetArray()->size(); weaponset++)
			{
				for (unsigned int weapon = 0; weapon < GameData::Instance()->getWeaponSet(weaponset)->getDataSet()->size(); weapon++)
				{
					m_pScorecardArray[levelset][level][weaponset].push_back(new Scorecard(levelset, level, weaponset, weapon));	// Number of weapons in each set
				}
			}
		}
	}

	// Make sure the first weapon and level available is always unlocked
	m_bUnlockedWeaponSets[0] = true;
	m_bUnlockedWeapons[0][0] = true;
	m_bUnlockedLevelSets[0] = true;
	m_bUnlockedLevels[0][0] = true;
}

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
		const char* CHILD_COLLECTABLE = "collectable";
		const char* CHILD_SCORECARD = "scorecard";
		const char* SCORECARD_NUMCOLLECTED = "numcollected";
		const char* SCORECARD_LEASTTOTALTIME = "leasttotaltime";
		const char* SCORECARD_LEASTGROUNDTIME = "leastgroundtime";
		const char* SCORECARD_LOWESTGROUNDTOTOTALTIMERATIO = "lowestgroundtototaltimeratio";
		const char* SCORECARD_FEWESTRELOADS = "fewestreloads";
		const char* SCORECARD_FEWESTSHOTSFIRED = "fewestshotsfired";
		const char* SCORECARD_LOWESTRELOADSTOSHOTSRATIO = "lowestreloadstoshotsratio";
		const char* SCORECARD_TOPSPEED = "topspeed";
		const char* SCORECARD_NUMBEROFATTEMPTS = "numberofattempts";
		const char* SCORECARD_NUMBEROFDEATHS = "numberofdeaths";
		const char* SCORECARD_NUMBEROFWINS = "numberofwins";
		const char* SCORECARD_LEASTDEATHSTOWIN = "leastdeathstowin";
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
			pElement[0] = pElement[0]->FirstChildElement(CHILD_WEAPONSET);

			// Iterate through the levelsets (CHILD_LEVELSET)
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]); // Identify the WeaponSet to iterate through
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVELSET); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVELSET))
			{
				// Iterate through the levels (CHILD_LEVEL)
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]); // Identify the LevelSet to iterate through
				for (pElement[2] = pElement[1]->FirstChildElement(CHILD_LEVEL); pElement[2] != nullptr; pElement[2] = pElement[2]->NextSiblingElement(CHILD_LEVEL))
				{
					// Read the level attributes
					pElement[2]->QueryUnsignedAttribute(ID, &ictr[2]);
					pElement[2]->QueryUnsignedAttribute(WEAPONID, &ictr[3]);
					std::cout << "WeaponSet: " << ictr[0] << " LevelSet: " << ictr[1] << " Level: " << ictr[2] << " WeaponId: " << ictr[3] << std::endl;
					setActiveWeapon(ictr[0], ictr[1], ictr[2], ictr[3]); // Currently this line has no controls in place for if the player has a weapon active belonging to a set which doesn't exist - the game will crash.
				}
			}
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " active weapons for each level loaded succssfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData UnlockedWeapons ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_UNLOCKEDWEAPONS);

		// Iterate through the weaponsets (CHILD_WEAPONSET)
		for (pElement[0] = pElement[0]->FirstChildElement(CHILD_WEAPONSET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET))
		{
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]);
			pElement[0]->QueryBoolAttribute(UNLOCKED, &bctr);
			setUnlockedWeaponSet(ictr[0], bctr);

			// Iterate through the weapons (CHILD_WEAPON)
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_WEAPON); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_WEAPON))
			{
				// Read the weapon attributes 
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]);
				pElement[1]->QueryBoolAttribute(UNLOCKED, &bctr);
				setUnlockedWeapon(ictr[0], ictr[1], bctr);
			}
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " unlocked weapons loaded successfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData UnlockedLevels ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_UNLOCKEDLEVELS);

		// Iterate through the levelsets (CHILD_LEVELSET)
		for (pElement[0] = pElement[0]->FirstChildElement(CHILD_LEVELSET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET))
		{
			// Set the Unlocked Level Set
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]);
			pElement[0]->QueryBoolAttribute(UNLOCKED, &bctr);
			setUnlockedLevelSet(ictr[0], bctr);

			// Iterate through the levels (CHILD_LEVEL)
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVEL); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVEL))
			{
				// Read the level attributes
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]);
				pElement[1]->QueryBoolAttribute(UNLOCKED, &bctr);
				setUnlockedLevel(ictr[0], ictr[1], bctr);

				// Iterate through the collectibles (CHILD_COLLECTIBLE)
				for (unsigned int index = 0; index < ictr[2]; index++)
				{
					setCollectible(ictr[0], ictr[1], ictr[3], false);
				}

				for (pElement[2] = pElement[1]->FirstChildElement(CHILD_COLLECTABLE); pElement[2] != nullptr; pElement[2] = pElement[2]->NextSiblingElement(CHILD_COLLECTABLE))
				{
					// Read the collectible unlocked attributes only
					pElement[2]->QueryUnsignedAttribute(ID, &ictr[3]);
					pElement[2]->QueryBoolAttribute(UNLOCKED, &bctr);
					setCollectible(ictr[0], ictr[1], ictr[3], bctr);
				}
			}
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " unlocked levels loaded successfully." << std::endl;

		/* ---- ---- ---- ---- ---- Load PlayerData ScoreCardData ---- ---- ---- ---- ---- */
		pElement[0] = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_SCORECARDDATA);
		// Iterate through the weaponsets (CHILD_LEVELSET)
		for (pElement[0] = pElement[0]->FirstChildElement(CHILD_LEVELSET); pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET))
		{
			pElement[0]->QueryUnsignedAttribute(ID, &ictr[0]);
			for (pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVEL); pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVEL))
			{
				pElement[1]->QueryUnsignedAttribute(ID, &ictr[1]);
				for (pElement[2] = pElement[1]->FirstChildElement(CHILD_WEAPONSET); pElement[2] != nullptr; pElement[2] = pElement[2]->NextSiblingElement(CHILD_WEAPONSET))
				{
					pElement[2]->QueryUnsignedAttribute(ID, &ictr[2]);
					for (pElement[3] = pElement[2]->FirstChildElement(CHILD_WEAPON); pElement[3] != nullptr; pElement[3] = pElement[3]->NextSiblingElement(CHILD_WEAPON))
					{
						pElement[3]->QueryUnsignedAttribute(ID, &ictr[3]);

						// Read the scorecard attributes
						int leastTotalTime = -1, leastGroundTime = -1, fewestReloads = -1, fewestShotsFired = -1;
						unsigned int numAttempts = 0, numDeaths = 0, numWins = 0;
						float lowestGroundToTotal = -1.0f, lowestReloadsToShots = -1.0f, leastDeathsToWin = -1.0f, topSpeed = -1.0f;
						pElement[3]->QueryUnsignedAttribute(SCORECARD_NUMCOLLECTED, &ictr[4]);
						pElement[3]->QueryIntAttribute(SCORECARD_LEASTTOTALTIME, &leastTotalTime);
						pElement[3]->QueryIntAttribute(SCORECARD_LEASTGROUNDTIME, &leastGroundTime);
						pElement[3]->QueryFloatAttribute(SCORECARD_LOWESTGROUNDTOTOTALTIMERATIO, &lowestGroundToTotal);
						pElement[3]->QueryIntAttribute(SCORECARD_FEWESTRELOADS, &fewestReloads);
						pElement[3]->QueryIntAttribute(SCORECARD_FEWESTSHOTSFIRED, &fewestShotsFired);
						pElement[3]->QueryFloatAttribute(SCORECARD_LOWESTRELOADSTOSHOTSRATIO, &lowestReloadsToShots);
						pElement[3]->QueryFloatAttribute(SCORECARD_TOPSPEED, &topSpeed);
						pElement[3]->QueryUnsignedAttribute(SCORECARD_NUMBEROFATTEMPTS, &numAttempts);
						pElement[3]->QueryUnsignedAttribute(SCORECARD_NUMBEROFDEATHS, &numDeaths);
						pElement[3]->QueryUnsignedAttribute(SCORECARD_NUMBEROFWINS, &numWins);
						pElement[3]->QueryFloatAttribute(SCORECARD_LEASTDEATHSTOWIN, &leastDeathsToWin);
						delete m_pScorecardArray[ictr[0]][ictr[1]][ictr[2]][ictr[3]];
						m_pScorecardArray[ictr[0]][ictr[1]][ictr[2]][ictr[3]] = new Scorecard( ictr[0], ictr[1], ictr[2], ictr[3], ictr[4],
							leastTotalTime, leastGroundTime, lowestGroundToTotal,
							fewestReloads, fewestShotsFired, lowestReloadsToShots,
							numDeaths, numWins, leastDeathsToWin, topSpeed, numAttempts );
						std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " scorecard for level " << ictr[0] << '.' << ictr[1] << ", weapon " << ictr[2] << '.' << ictr[3] << " loaded successfully." << std::endl;
					}
					std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " all scorecards for level " << ictr[0] << '.' << ictr[1] << ", weaponset " << ictr[2] << " loaded successfully." << std::endl;
				}
				std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " all scorecards for level " << ictr[0] << '.' << ictr[1] << " loaded successfully." << std::endl;
			}
			std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " all scorecards for level set " << ictr[0] << " loaded successfully." << std::endl;
		}
		std::cout << "Player " << GameData::Instance()->getPlayerDataSet()->getDataSet()->size() << " all scorecards loaded successfully." << std::endl;
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

void PlayerData::printScorecardArray()
{
	const std::string _NumberOf = "Number of ";
	const std::string _ScordcardArray = "Scorecard Array: ";
	const std::string _LevelSet = "Level Set";
	const std::string _Level = "Level";
	const std::string _WeaponSet = "Weapon Set";
	const std::string _Weapon = "Weapon";

	std::cout << _ScordcardArray << ": " << _NumberOf << _LevelSet << "s: " << GameData::Instance()->getLevelSetArray()->size() << std::endl;
	for (unsigned int levelSetId = 0; levelSetId < GameData::Instance()->getLevelSetArray()->size(); levelSetId++)
	{
		std::cout << _LevelSet << ": " << levelSetId << ": " << _NumberOf << _Level << "s: " << GameData::Instance()->getLevelSet(levelSetId)->getDataSet()->size() << std::endl;
		for (unsigned int levelId = 0; levelId < GameData::Instance()->getLevelSet(levelSetId)->getDataSet()->size(); levelId++)
		{
			std::cout << _Level << ": " << levelId << ": " << _NumberOf << _WeaponSet << "s: " << GameData::Instance()->getWeaponSetArray()->size() << std::endl;
			for (unsigned int weaponSetId = 0; weaponSetId < GameData::Instance()->getWeaponSetArray()->size(); weaponSetId++)
			{
				std::cout << _WeaponSet << ": " << weaponSetId << ": " << _NumberOf << _Weapon << "s: " << GameData::Instance()->getWeaponSet(weaponSetId)->getDataSet()->size() << std::endl;
				for (unsigned int weaponId = 0; weaponId < GameData::Instance()->getWeaponSet(weaponSetId)->getDataSet()->size(); weaponId++)
				{
					std::cout << _Weapon << ": " << weaponId << ": " << std::endl;
					m_pScorecardArray[levelSetId][levelId][weaponSetId][weaponId]->Print();
				}
			}
		}
	}
}
