#include "DataSet.h"
#include "PlayerData.h"
#include "Level.h"
#include "Weapon.h"
#include "Scorecard.h"
#include "Tile.h"
#include "TextureManager.h"
#include "Engine.h"

/* ---- ---- ---- ---- ---- ---- ---- PlayerData Set loadFromXML ---- ---- ---- ---- ---- ---- ---- */
/** The first thing the function needs to know is whether you're:
adding a new player (NONE), unloading a specific player (DEFAULT), or unloading all players (ALL)?
* The second thing the function needs to know is whether you're:
only unloading (NONE), loading a specific player (DEFAULT), or loading the whole DataFile (ALL)?
* The final thing the function needs to know is whether you're:
getting the player name from the istream as the function runs (ISTREAM), or from somewhere else (not yet implemented)?*/
template<>
inline bool DataSet_1D<PlayerData>::LoadFromXML(Flags unloadFlags, Flags loadFlags)
{
	/* ---- ---- ---- ---- ---- Unload Anything ---- ---- ---- ---- ---- */
	switch (unloadFlags)
	{
	case DataSet::Flags::NONE:
		break;
	case DataSet::Flags::ALL:
		Clean(Flags::ALL);
	default:
	case DataSet::Flags::DEFAULT:
	case DataSet::Flags::FROMISTREAM:
		//TGS02::getInputfromIstream();
		Clean(DataSet::Flags::DEFAULT);
		break;
	}

	/* ---- ---- ---- ---- ---- Load Anything ---- ---- ---- ---- ---- */
	if (loadFlags != DataSet::Flags::NONE)
	{
		// Create the XML document
		tinyxml2::XMLDocument xmlDoc;
		if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
		{
			printFileName("PlayerDataSet::LoadFromXML: ");
			xmlDoc.PrintError();
			return xmlDoc.Error();
		}

		// Define the temporary storage variables
		std::string input;
		const char* ROOT = "playerdataset";
		const char* CHILD_PLAYERDATA = "player";
		const char* ATTRIBUTE_NAME = "name";
		tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
		tinyxml2::XMLElement* pElement;

		/* ---- ---- ---- ---- ---- Load PlayerDataSet ---- ---- ---- ---- ---- */
		// Get the playername input
		if (loadFlags == DataSet::Flags::DEFAULT || loadFlags == DataSet::Flags::FROMISTREAM || loadFlags == DataSet::Flags::DEFAULT_FROMISTREAM)
		{
			std::cout << "Loading Player Data..." << std::endl;
			//input = TGS02::getInputfromIstream();
			input = ""; //temporary
		}
		else
		{
			input = "";
		}

		// Iterate through the loop
		pElement = xmlDoc.FirstChildElement(ROOT)->FirstChildElement(CHILD_PLAYERDATA);
		while (pElement != nullptr)
		{
			std::cout << pElement->Attribute(ATTRIBUTE_NAME) << std::endl;
			std::string nameInFile = pElement->Attribute(ATTRIBUTE_NAME);
			// If flags are set to load all, carry on.
			// If flags are set to load specific, carry on only if the read value the requested one.
			// If flags are set to load nothing, it won't have gotten this deep anyway.
			std::cout << "loadFlags: " << static_cast<int>(loadFlags) << std::endl;
			if (loadFlags == DataSet_1D<PlayerData>::Flags::ALL ||
				((loadFlags == DataSet::Flags::DEFAULT || loadFlags == DataSet::Flags::FROMISTREAM && nameInFile == input || loadFlags == DataSet::Flags::DEFAULT_FROMISTREAM) && nameInFile == input))
			{
				m_pDataSet.push_back(new PlayerData(nameInFile));
				m_pDataSet.back()->LoadFromXML();
			}
			pElement = pElement->NextSiblingElement(CHILD_PLAYERDATA);
		}
	}
	return true;
}

template class DataSet_1D<PlayerData>;

/* ---- ---- ---- ---- ---- ---- ---- Weapon Set loadFromXML ---- ---- ---- ---- ---- ---- ---- */
template<>
inline bool DataSet_1D<Weapon>::LoadFromXML(Flags unloadFlags, Flags loadFlags)
{
	//Create the XML document
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
	{
		printFileName("LevelSet::LoadFromXML: ");
		xmlDoc.PrintError();
		return xmlDoc.Error();
	}

	// Define the tags and temporary storage variables
	const char* ROOT = "gamedata";
	const char* CHILD_WEAPONSET = "weaponset";
	const char* CHILD_WEAPON = "weapon";
	const char* ATTRIBUTE_ID = "id";
	const char* ATTRIBUTE_NAME = "name";
	const char* ATTRIBUTE_RECOIL = "recoil";
	const char* ATTRIBUTE_REFIRERATE = "refirerate";
	const char* ATTRIBUTE_RELOADRATE = "reloadrate";
	const char* ATTRIBUTE_MAXSHOTS = "maxshots";
	const char* ATTRIBUTE_MAXRELOADS = "maxreloads";
	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
	tinyxml2::XMLElement* pElement[2] = { nullptr };

	// Scan for the correct WeaponSet
	pElement[0] = pRoot->FirstChildElement(CHILD_WEAPONSET);
	for (unsigned int setId; pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET))
	{
		pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &setId);
		if (setId == getId())
		{
			// Populate each Weapon in the set
			std::cout << "Loading weaponSet Id: " << setId << std::endl;
			pElement[1] = pElement[0]->FirstChildElement(CHILD_WEAPON);
			for (unsigned int itemId; pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_WEAPON))
			{
				// Store all of the attributes for the element before attempting to continue
				std::string name;
				float recoil;
				unsigned int refireRate, reloadRate, maxShots, maxReloads;
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_ID, &itemId);
				name = pElement[1]->Attribute(ATTRIBUTE_NAME);
				pElement[1]->QueryFloatAttribute(ATTRIBUTE_RECOIL, &recoil);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_REFIRERATE, &refireRate);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_RELOADRATE, &reloadRate);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_MAXSHOTS, &maxShots);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_MAXRELOADS, &maxReloads);
				m_pDataSet.push_back(new Weapon(itemId, name, recoil, refireRate, reloadRate, maxShots, maxReloads));
				std::cout << m_pDataSet.back()->getName() << ": Weapon data " << itemId << " in set " << setId << " loaded successfully." << std::endl;
			}
		}
		std::cout << getName() << ": WeaponSet " << setId << " loaded successfully." << std::endl;
		//pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &setId);
		//std::cout << "Targetting weaponSet Id: " << setId << std::endl;
	}
	return true;
}

template class DataSet_1D<Weapon>;

/* ---- ---- ---- ---- ---- ---- ---- Level Set loadFromXML ---- ---- ---- ---- ---- ---- ---- */
template<>
inline bool DataSet_1D<Level>::LoadFromXML(Flags unloadFlags, Flags loadFlags)
{
	//Create the XML document
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
	{
		printFileName("LevelSet::LoadFromXML: ");
		xmlDoc.PrintError();
		return xmlDoc.Error();
	}

	// Define the temporary storage variables
	const char* ROOT = "gamedata";
	const char* CHILD_LEVELSET = "levelset";
	const char* CHILD_LEVEL = "level";
	const char* ATTRIBUTE_ID = "id";
	const char* ATTRIBUTE_NAME = "name";
	const char* ATTRIBUTE_FILENAME = "filename";
	const char* ATTRIBUTE_COVERFILE = "coverfile";
	const char* ATTRIBUTE_UNLOCKCODE = "unlockcode";
	const char* ATTRIBUTE_COLLECTIBLES = "collectibles";
	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
	tinyxml2::XMLElement* pElement[2];

	// Scan for the correct LevelSet
	pElement[0] = pRoot->FirstChildElement(CHILD_LEVELSET);
	for (unsigned int setId; pElement[0] != nullptr; pElement[0] = pElement[0]->NextSiblingElement(CHILD_LEVELSET))
	{
		pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &setId);
		if (setId == getId())
		{
			// Populate each Level in the set
			pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVEL);
			for (unsigned int itemId; pElement[1] != nullptr; pElement[1] = pElement[1]->NextSiblingElement(CHILD_LEVEL))
			{
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_ID, &itemId);

				// Store all of the attributes for the element before attempting to continue
				std::string filename, name, coverfile, unlockcode;
				unsigned int id, collectibles;
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_ID, &id);
				filename = pElement[1]->Attribute(ATTRIBUTE_FILENAME);
				filename = "GameData/" + filename;
				name = pElement[1]->Attribute(ATTRIBUTE_NAME);
				coverfile = pElement[1]->Attribute(ATTRIBUTE_COVERFILE);
				unlockcode = pElement[1]->Attribute(ATTRIBUTE_UNLOCKCODE);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_COLLECTIBLES, &collectibles);
				m_pDataSet.push_back(new Level(id, name, filename, coverfile, unlockcode, collectibles));
				std::cout << "Level data " << itemId << " in set " << setId << " loaded successfully." << std::endl;
			}
			std::cout << "Level data set " << setId << " loaded successfully." << std::endl;
		}
	}
	std::cout << "All level data sets loaded successfully." << std::endl;
	return true;
}

template class DataSet_1D<Level>;

/* ---- ---- ---- ---- ---- ---- ---- Tile Set loadFromXML ---- ---- ---- ---- ---- ---- ---- */
template<>
inline bool DataSet_1D<Tile>::LoadFromXML(Flags unloadFlags, Flags loadFlags)
{
	//Create the XML document
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
	{
		printFileName("TileSet::LoadFromXML: ");
		xmlDoc.PrintError();
		return xmlDoc.Error();
	}

	// Define the temporary storage variables
	const char* ROOT = "tileset";
	const char* CHILD_TILE = "tile";
	const char* CHILD_PROPERTIES = "properties";
	const char* CHILD_PROPERTY = "property";
	const char* CHILD_IMAGE = "image";
	const char* CHILD_OBJECTGROUP = "objectgroup";
	const char* CHILD_OBJECT = "object";
	const char* CHILD_ANIMATION = "animation";
	const char* CHILD_FRAME = "frame";
	const char* ATTRIBUTE_ID = "id";
	const char* ATTRIBUTE_NAME = "name";
	const char* ATTRIBUTE_TILEWIDTH = "tilewidth";
	const char* ATTRIBUTE_TILEHEIGHT = "tileheight";
	const char* ATTRIBUTE_TILECOUNT = "tilecount";
	const char* ATTRIBUTE_X = "x";
	const char* ATTRIBUTE_Y = "y";
	const char* ATTRIBUTE_WIDTH = "width";
	const char* ATTRIBUTE_HEIGHT = "height";
	const char* ATTRIBUTE_TYPE = "type";
	const char* ATTRIBUTE_SOURCE = "source";
	const char* ATTRIBUTE_VALUE = "value";
	const char* ATTRIBUTE_TILEID = "tileid";
	const char* ATTRIBUTE_DURATION = "duration";
	const char* TYPE_BACKGROUNDTILE = "BackgroundTile";
	const char* TYPE_STATICTILE = "StaticTile";
	const char* TYPE_INTERACTIVETILE = "InteractiveTile";
	std::string PROPERTY_DRAG = "drag";
	std::string PROPERTY_FORCE_X = "force_x";
	std::string PROPERTY_FORCE_Y = "force_y";
	std::string PROPERTY_JUMPFORCE_X = "jumpforce_x";
	std::string PROPERTY_JUMPFORCE_Y = "jumpforce_y";
	std::string PROPERTY_JUMPFORCEMAX = "jumpforcemax";
	std::string PROPERTY_MAXDRAG = "maxdrag";
	std::string PROPERTY_MAXSPEED = "maxspeed";
	std::string PROPERTY_INTERACTIONTYPE = "interactiontype";
	std::string PROPERTY_ANIMATEONINTERACTION = "animateoninteraction";
	std::string PROPERTY_VANISHONINTERACTION = "vanishoninteraction";
	std::string PROPERTY_JUMPIMPULSE_X = "jumpimpulse_x";
	std::string PROPERTY_JUMPIMPULSE_Y = "jumpimpulse_y";
	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
	tinyxml2::XMLElement* pElement[2];
	unsigned int id[2];

	// Load the tileset
	std::string name;
	int tilewidth, tileheight;
	unsigned int tilecount;
	pElement[0] = xmlDoc.FirstChildElement(ROOT);
	name = pElement[0]->Attribute(ATTRIBUTE_NAME);
	pElement[0]->QueryIntAttribute(ATTRIBUTE_TILEWIDTH, &tilewidth);
	pElement[0]->QueryIntAttribute(ATTRIBUTE_TILEHEIGHT, &tileheight);
	pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_TILECOUNT, &tilecount);

	// Load each tile
	for (pElement[0] = pRoot->FirstChildElement(CHILD_TILE);
		pElement[0] != nullptr;
		pElement[0] = pElement[0]->NextSiblingElement(CHILD_TILE))
	{
		// Define the temporary storage variables with default values
		std::string type;
		bool animateoninteraction = false, vanishoninteraction = false;
		int src_x = 0, src_y = 0, src_w, src_h, interactiontype;
		const char* src_file;
		float drag, force_x, force_y, maxdrag, maxspeed,	// Common to all world tiles
			jumpforce_x, jumpforce_y, jumpforcemax,			// Common to background tiles
			jumpimpulse_x, jumpimpulse_y,					// Common to static and dynamic tiles
			col_x, col_y, col_w, col_h;						// Common to static, dynamic, and interactive tiles
		SDL_Rect src, dst = { 0, 0, tilewidth, tileheight };
		SDL_FRect col;
		SDL_Texture* tex;

		// Determine the tile id and type
		pElement[0]->QueryUnsignedAttribute(ATTRIBUTE_ID, &id[0]);
		type = pElement[0]->Attribute(ATTRIBUTE_TYPE);

		// Go through the tile properties
		pElement[1] = pElement[0]->FirstChildElement(CHILD_PROPERTIES);
		if (pElement[1] != nullptr)
		{
			for (pElement[1] = pElement[1]->FirstChildElement(CHILD_PROPERTY);
				pElement[1] != nullptr;
				pElement[1] = pElement[1]->NextSiblingElement(CHILD_PROPERTY))
			{
				// Determine the property type and save its values
				std::string prop;
				prop = pElement[1]->Attribute(ATTRIBUTE_NAME);
				if (prop == PROPERTY_DRAG)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &drag);
				if (prop == PROPERTY_FORCE_X)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &force_x);
				if (prop == PROPERTY_FORCE_Y)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &force_y);
				if (prop == PROPERTY_JUMPFORCE_X)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &jumpforce_x);
				if (prop == PROPERTY_JUMPFORCE_Y)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &jumpforce_y);
				if (prop == PROPERTY_JUMPFORCEMAX)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &jumpforcemax);
				if (prop == PROPERTY_MAXDRAG)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &maxdrag);
				if (prop == PROPERTY_MAXSPEED)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &maxspeed);
				if (prop == PROPERTY_INTERACTIONTYPE)
					pElement[1]->QueryIntAttribute(ATTRIBUTE_VALUE, &interactiontype);
				if (prop == PROPERTY_ANIMATEONINTERACTION)
					pElement[1]->QueryBoolAttribute(ATTRIBUTE_VALUE, &animateoninteraction);
				if (prop == PROPERTY_VANISHONINTERACTION)
					pElement[1]->QueryBoolAttribute(ATTRIBUTE_VALUE, &vanishoninteraction);
				if (prop == PROPERTY_JUMPIMPULSE_X)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &jumpimpulse_x);
				if (prop == PROPERTY_JUMPIMPULSE_Y)
					pElement[1]->QueryFloatAttribute(ATTRIBUTE_VALUE, &jumpimpulse_y);
			}
		}

		// Determine the image properties
		pElement[1] = pElement[0]->FirstChildElement(CHILD_IMAGE);
		pElement[1]->QueryIntAttribute(ATTRIBUTE_WIDTH, &src_w);
		pElement[1]->QueryIntAttribute(ATTRIBUTE_HEIGHT, &src_h);
		pElement[1]->QueryStringAttribute(ATTRIBUTE_SOURCE, &src_file);
		tex = TextureManager::LoadTexture(Engine::Instance().GetRenderer(), src_file + 3);	// The + 3 removes the first three characters "../" from the string, since the TextureManager.h is one directory higher in the heirarchy than the *.tsx files.
		//std::cout << src_file + 3 << tex << ' ';
		src = { src_x, src_y, src_w, src_h };

		// Determine the collision properties
		pElement[1] = pElement[0]->FirstChildElement(CHILD_OBJECTGROUP);
		if (pElement[1] != nullptr)
		{
			for (pElement[1] = pElement[1]->FirstChildElement(CHILD_OBJECT);
				pElement[1] != nullptr;
				pElement[1] = pElement[1]->NextSiblingElement(CHILD_OBJECT))
			{
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_ID, &id[1]);
				pElement[1]->QueryFloatAttribute(ATTRIBUTE_X, &col_x);
				pElement[1]->QueryFloatAttribute(ATTRIBUTE_Y, &col_y);
				pElement[1]->QueryFloatAttribute(ATTRIBUTE_WIDTH, &col_w);
				pElement[1]->QueryFloatAttribute(ATTRIBUTE_HEIGHT, &col_h);
				col = { col_x, col_y, col_w, col_h};
			}
		}

		// Create the tile object
		//std::cout << "Initializing Tile template at position " << m_pDataSet.size() << " in the set." << std::endl;
		if (type == TYPE_BACKGROUNDTILE)
		{
			m_pDataSet.push_back(new BackgroundTile(tex, src, dst,
				drag, maxspeed, maxdrag, glm::vec2{force_x, force_y},
				glm::vec2{jumpforce_x, jumpforce_y}, jumpforcemax));
		}
		else if (type == TYPE_STATICTILE)
		{
			m_pDataSet.push_back(new StaticTile(tex, src, dst, col,
				drag, maxspeed, maxdrag, glm::vec2{force_x, force_y},
				glm::vec2{jumpimpulse_x, jumpimpulse_y}, static_cast<StaticTile::Type>(interactiontype)));
		}
		else if (type == TYPE_INTERACTIVETILE)
		{
			m_pDataSet.push_back(new InteractiveTile(tex, src, dst, col, static_cast<InteractiveTile::Type>(interactiontype), animateoninteraction, vanishoninteraction));
		}

		// Determine the animation properties
		pElement[1] = pElement[0]->FirstChildElement(CHILD_ANIMATION);
		if (pElement[1] != nullptr)
		{
			if (type == TYPE_STATICTILE || type == TYPE_INTERACTIVETILE)
			{
				m_pDataSet.back()->setFrameSet(new CollidableFrameSet);
			}
			else
			{
				m_pDataSet.back()->setFrameSet(new FrameSet);
			}
			unsigned int tileid, duration;
			for (pElement[1] = pElement[1]->FirstChildElement(CHILD_FRAME);
				pElement[1] != nullptr;
				pElement[1] = pElement[1]->NextSiblingElement(CHILD_FRAME))
			{
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_TILEID, &tileid);
				pElement[1]->QueryUnsignedAttribute(ATTRIBUTE_DURATION, &duration);
				m_pDataSet.back()->getFrameSet()->addFrame(tileid, duration);
			}
		}

		if (m_pDataSet[id[0]] == nullptr)
		{
			std::cerr << "ERROR: Tile Index/Id mismatch." << std::endl;
		}
		else
		{
			std::cout << "Tile at index " << id[0] << " in set " << getId() << " loaded successfully." << std::endl;
		}
	}
	std::cout << "All tiles in tileset " << getId() << " loaded successfully." << std::endl;
	for (unsigned int tileId = 0; tileId < m_pDataSet.size(); tileId++)
	{
		FrameSet* fsptr = m_pDataSet[tileId]->getFrameSet();
		if (fsptr != nullptr)
		{
			CollidableFrameSet* cfsptr = dynamic_cast<CollidableFrameSet*>(fsptr);
			if (cfsptr != nullptr)
			{
				cfsptr->populateFrameSet(*this);
			}
			else
			{
				fsptr->populateFrameSet(*this);
			}
		}
	}
	return true;
}

template class DataSet_1D<Tile>;

/* ---- ---- ---- ---- ---- ---- ---- Scorecard Set loadFromXML ---- ---- ---- ---- ---- ---- ---- */
template<>
inline bool DataSet_2D<Scorecard>::LoadFromXML(Flags unloadFlags, Flags loadFlags)
{
	// Create the XML document
	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.LoadFile(getFileName().c_str()) != 0)	// Check the file loaded successfully
	{
		printFileName("ScorecardSet::LoadFromXML: ");
		xmlDoc.PrintError();
		return xmlDoc.Error();
	}

	// Define the temporary storage variables
	std::string sctr;
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
	const char* CHILD_COLLECTIBLESET = "collectibleset";
	const char* CHILD_COLLECTIBLE = "collectible";
	const char* CHILD_SCORECARDSET = "scorecardset";
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
	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement(ROOT);
	tinyxml2::XMLElement* pElement[5] = { nullptr };

	// Iterate through the weaponsets (CHILD_WEAPONSET)
	pElement[0] = pRoot->FirstChildElement(CHILD_SCORECARDDATA)->FirstChildElement(CHILD_WEAPONSET);
	for (unsigned int weaponSetId = 0; pElement[0] != nullptr; weaponSetId++, pElement[0] = pElement[0]->NextSiblingElement(CHILD_WEAPONSET))
	{
		if (weaponSetId == getId())
		{
			// Iterate through the levelsets (CHILD_LEVELSET)
			pElement[1] = pElement[0]->FirstChildElement(CHILD_LEVELSET);
			for (unsigned int levelSetId = 0; pElement[1] != nullptr; levelSetId++, pElement[1]->NextSiblingElement(CHILD_LEVELSET))
			{
				if (levelSetId == getId_y())
				{
					// Iterate through the levels (CHILD_LEVEL)
					pElement[2] = pElement[1]->FirstChildElement(CHILD_LEVEL);
					for (unsigned int levelId = 0; pElement[2] != nullptr; levelId++, pElement[2]->NextSiblingElement(CHILD_LEVEL))
					{
						if (levelId == getId_z())
						{
							/* ---- ---- ---- Correct Scorecard SET identified, now to read and store it! ---- ---- ---- */
							// Iterate through the weapons (CHILD_WEAPON)
							pElement[3] = pElement[2]->FirstChildElement(CHILD_WEAPON);
							for (unsigned int weaponId = 0; pElement[3] != nullptr; weaponId++, pElement[3]->NextSiblingElement(CHILD_WEAPON))
							{
								//m_pDataSet.push_back(new std::vector<Scorecard*>);

								// Iterate through the individual scorecards (CHILD_COLLECTIBLE)
								pElement[4] = pElement[3]->FirstChildElement(CHILD_COLLECTIBLE);
								int leastTotalTime = -1, leastGroundTime = -1, fewestReloads = -1, fewestShotsFired = -1;
								unsigned int numAttempts = 0, numDeaths = 0, numWins = 0;
								float lowestGroundToTotal = -1, lowestReloadsToShots = -1, leastDeathsToWin = -1, topSpeed = -1;
								for (unsigned int collectibleId = 0; pElement[4] != nullptr; collectibleId++, pElement[4]->NextSiblingElement(CHILD_COLLECTIBLE))
								{
									// Read the scorecard attributes
									pElement[4]->QueryIntAttribute(SCORECARD_LEASTTOTALTIME, &leastTotalTime);
									pElement[4]->QueryIntAttribute(SCORECARD_LEASTGROUNDTIME, &leastGroundTime);
									pElement[4]->QueryFloatAttribute(SCORECARD_LOWESTGROUNDTOTOTALTIMERATIO, &lowestGroundToTotal);
									pElement[4]->QueryIntAttribute(SCORECARD_FEWESTRELOADS, &fewestReloads);
									pElement[4]->QueryIntAttribute(SCORECARD_FEWESTSHOTSFIRED, &fewestShotsFired);
									pElement[4]->QueryFloatAttribute(SCORECARD_LOWESTRELOADSTOSHOTSRATIO, &lowestReloadsToShots);
									pElement[4]->QueryFloatAttribute(SCORECARD_TOPSPEED, &topSpeed);
									pElement[4]->QueryUnsignedAttribute(SCORECARD_NUMBEROFATTEMPTS, &numAttempts);
									pElement[4]->QueryUnsignedAttribute(SCORECARD_NUMBEROFDEATHS, &numDeaths);
									pElement[4]->QueryUnsignedAttribute(SCORECARD_NUMBEROFWINS, &numWins);
									pElement[4]->QueryFloatAttribute(SCORECARD_LEASTDEATHSTOWIN, &leastDeathsToWin);
									//m_pDataSet.back()->push_back(new Scorecard(weaponSetId, weaponId, collectibleId,
									//	leastTotalTime, leastGroundTime, lowestGroundToTotal,
									//	fewestReloads, fewestShotsFired, lowestReloadsToShots,
									//	numDeaths, numWins, leastDeathsToWin, topSpeed, numAttempts));
								}
								std::cout << "All scorecard data using weapon " << weaponId << " for level " << levelId << " in level set " << levelSetId << " for " << weaponSetId << " loaded successfully." << std::endl;
							}
							std::cout << "All scorecard data for level " << levelId << " in level set " << levelSetId << " for " << weaponSetId << " loaded successfully." << std::endl;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return true;
}

template class DataSet_2D<Scorecard>;

template <class T>
void DataSet_1D<T>::Clean(Flags unloadFlags)
{
	for (unsigned int index = 0; index < m_pDataSet.size(); index++)
	{
		delete m_pDataSet[index];
		m_pDataSet[index] = nullptr;
	}
	m_pDataSet.clear();
	m_pDataSet.shrink_to_fit();
}

template <class T>
void DataSet_2D<T>::Clean(Flags flags)
{
	for (unsigned int xIndex = 0; xIndex < m_pDataSet.size(); xIndex++)
	{
		for (unsigned int yIndex = 0; yIndex < m_pDataSet[xIndex]->size(); yIndex++)
		{
			delete m_pDataSet[xIndex]->at(yIndex);
			m_pDataSet[xIndex]->at(yIndex) = nullptr;
		}
		m_pDataSet[xIndex]->clear();
		m_pDataSet[xIndex]->shrink_to_fit();
		delete m_pDataSet[xIndex];
	}
	m_pDataSet.clear();
	m_pDataSet.shrink_to_fit();
}

template<class T>
void DataSet_2D<T>::Print()
{
	for (unsigned int xIndex = 0; xIndex < m_pDataSet.size(); xIndex++)
	{
		for (unsigned int yIndex = 0; yIndex < m_pDataSet[xIndex]->size(); yIndex++)
		{
			m_pDataSet[xIndex]->at(yIndex)->Print();
		}
	}
}
