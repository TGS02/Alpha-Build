#pragma once
#include <string>
#include <vector>
#include "DataSet.h"
#include "Tile.h"
#include "Level.h"
#include "Weapon.h"
#include "PlayerData.h"
#define TGS02_GAMEDATAFILE "GameData/GameData.xml"
#define TGS02_PLAYERDATAFILE "GameData/PlayerData.xml"

// Class to store overall data for the entire game
class GameData
{
private:
	std::string m_strFileName;								// The name of the GameData file
	std::vector<DataSet_1D<Weapon>*> m_pWeaponSetArray;	// Vector of WeaponSet pointers, individual weapons are accessed through the set [setIndex]->getDatum(weaponIndex)
	std::vector<DataSet_1D<Level>*> m_pLevelSetArray;		// Vector of LevelSet pointers, individual levels are accessed through the set [setIndex]->getDatum(levelIndex)
	DataSet_1D<PlayerData> m_pPlayerDataSet;				// PlayerDataSet pointer, individual players are accessed through the set getDatum(playerIndex)
	GameData() : m_strFileName(TGS02_GAMEDATAFILE), m_pPlayerDataSet(1, "PlayerDataSet", TGS02_PLAYERDATAFILE) {}
	void setFileName(std::string name) { m_strFileName = name; }
public:
	// Class enumerations
	/*For now: Pass NONE and ALL to initialize the game with all data in all sets.
	* NONE = 0, un/load nothing
	* INIT = 1, un/load initial data
	* PLAYERDATA = 2, un/load PlayerData (required input from player)
	* WEAPONSET = 4, un/load WeaponSet(s), will load all sets by default
	* LEVELSET = 8, un/load LevelSet(s), will load all sets by default
	* ALL = 15, un/load all data in all sets
	* ACTIVE = 16, un/load only active data (implies POPULATE_PLAYERDATA)
	* INACTIVE = 32, un/load only inactive data (implies POPULATE_PLAYERDATA)*/
	enum class Flags { NONE = 0, INIT = 1, PLAYERDATA = 2, WEAPONSET = 4, LEVELSET = 8, ALL = 15, ACTIVE = 16, INACTIVE = 32 };
	friend DataSet;

	// System functions
	bool LoadFromXML(Flags unloadFlags = Flags::ALL, Flags loadFlags = Flags::ALL);
	void Clean(Flags unloadFlags = Flags::ALL);
	static GameData* Instance();

	// Mutator functions

	// Accessor functions
	std::string getFileName() { return m_strFileName; }
	std::vector<DataSet_1D<Weapon>*>* getWeaponSetArray() { return &m_pWeaponSetArray; }
	DataSet_1D<Weapon>* getWeaponSet(unsigned int index) { return m_pWeaponSetArray[index]; }
	//Weapon* getWeapon(unsigned int setIndex, unsigned int weaponIndex) { return m_pWeaponSetArray[setIndex]->getDatum(weaponIndex); }
	std::vector<DataSet_1D<Level>*>* getLevelSetArray() { return &m_pLevelSetArray; }
	DataSet_1D<Level>* getLevelSet(unsigned int index) { return m_pLevelSetArray[index]; }
	//Level* getLevel(unsigned int setIndex, unsigned int levelIndex) { return m_pLevelSetArray[setIndex]->getDatum(levelIndex); }
	DataSet_1D<PlayerData>* getPlayerDataSet() { return &m_pPlayerDataSet; }
	//PlayerData* getPlayerData(unsigned int index) { return m_pPlayerDataSet.getDatum(index); }
};
