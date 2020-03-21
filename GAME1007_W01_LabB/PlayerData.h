#pragma once
#include <vector>
#include "Scorecard.h"

class PlayerData
{
private:
	// The player has an active weapon set
	// and an active weapon for EACH level for EACH set
	// The player also has an active level set, sure

	// In order to create any single player object, I need to be aware of
	// The number of weapon sets and the number of weapons in each
	// The number of level sets and the number of levels in each

	// The player then reads the two dimensional arrays for their unlocked weapons and levels
	// And stores a locked status for every level in the set, not in their data
	// Or eliminates their data for every datum in their data not in the set
	std::string m_strName;
	std::string m_strBodyTextureFileName;
	std::string m_strArmTextureFileName;
	unsigned int m_iNumCollected;
	unsigned int m_iNumSpent;
	std::vector<std::vector<std::vector<bool> > > m_bCollectibleList;	// This 3D array stores the boolean collected status for each [LevelSet][Level][Collectible] the player has ever managed to get.
	unsigned int m_iActiveWeaponSet;
	std::vector<std::vector<std::vector<unsigned int> > > m_iActiveWeapon;	// This 3D array stores the active Weapon id for each [WeaponSet][LevelSet][Level]
	unsigned int m_iActiveLevelSet;
	std::vector<unsigned int> m_iActiveLevel;
	std::vector<bool> m_bUnlockedWeaponSets;
	std::vector<std::vector<bool> > m_bUnlockedWeapons;
	std::vector<bool> m_bUnlockedLevelSets;
	std::vector<std::vector<bool> > m_bUnlockedLevels;
	std::vector<std::vector<std::vector<std::vector<Scorecard* > > > > m_pScorecardArray;	// This 4D array stores the Scorecard pointer for each [LevelSet][Level][WeaponSet][Weapon].
public:
	// Class enumerations
	/*For now: Ignore this.
	* these flags are for determining if the scorecards stored within the player should be un/loaded for
	all [WeaponSet][LevelSet][Level]s, only for the [Level]s in the active sets, or only for the individual active Level itself.*/
	//static enum class Flags { NONE = 0 };

	// System functions
	PlayerData(std::string name);
	~PlayerData() { Clean(); }
	virtual bool LoadFromXML();
	virtual bool SaveToXML();
	virtual void Clean();

	// Mutator functions
	virtual void setName(std::string name) { m_strName = name; }
	virtual void setBodyTextureFileName(std::string filename) { m_strBodyTextureFileName = filename; }
	virtual void setArmTextureFileName(std::string filename) { m_strArmTextureFileName = filename; }
	virtual void setNumCollected(unsigned int num) { m_iNumCollected = num; } // Use with extreme caution!
	virtual void setNumSpent(unsigned int num) { m_iNumSpent = num; }
	virtual void setCollectible(unsigned int levelsetId, unsigned int levelId, unsigned int collectibleId, bool val) { m_bCollectibleList[levelsetId][levelId][collectibleId] = val; }
	virtual void setActiveWeaponSet(unsigned int indexId) { m_iActiveWeaponSet = indexId; }
	virtual void setActiveWeapon(unsigned int weaponsetId, unsigned int levelsetId, unsigned int levelId, unsigned int weaponId) { m_iActiveWeapon[weaponsetId][levelsetId][levelId] = weaponId; }
	virtual void setActiveWeaponInCurrenSet(unsigned int levelId, unsigned int weaponId) { m_iActiveWeapon[getActiveWeaponSet()][getActiveLevelSet()][levelId] = weaponId; }
	virtual void setActiveLevelSet(unsigned int indexId) { m_iActiveLevelSet = indexId; }
	virtual void setUnlockedWeaponSet(unsigned int setId, bool val) { m_bUnlockedWeaponSets[setId] = val; }
	virtual void setUnlockedWeapon(unsigned int setId, unsigned int weaponId, bool val) { m_bUnlockedWeapons[setId][weaponId] = val; } // Set the unlocked status of the Weapon at [WeaponSetId][WeaponId] to locked(0/false) or unlocked(1/true)
	virtual void setUnlockedLevelSet(unsigned int setId, bool val) { m_bUnlockedLevelSets[setId] = val; }
	virtual void setUnlockedLevel(unsigned int setId, unsigned int levelId, bool val) { m_bUnlockedLevels[setId][levelId] = val; } // Set the unlocked status of the Level at [LevelSetId][LevelId] to locked(0/false) or unlocked(1/true)

	// Accessor functions
	virtual std::string getName() { return m_strName; }
	virtual std::string getFileName() { return ("GameData/" + m_strName + ".xml"); }
	virtual std::string getBodyTextureFileName() { return m_strBodyTextureFileName; }
	virtual std::string getArmTextureFileName() { return m_strArmTextureFileName; }
	virtual unsigned int getNumCollected() { return m_iNumCollected; }
	virtual unsigned int getNumSpent() { return m_iNumSpent; }
	virtual unsigned int getNumLeft() { return m_iNumCollected - m_iNumSpent; }
	virtual bool getCollectible(unsigned int levelsetId, unsigned int levelId, unsigned int collectibleId) { return m_bCollectibleList[levelsetId][levelId][collectibleId]; }	// Which ones were gathered
	virtual unsigned int getActiveWeaponSet() { return m_iActiveWeaponSet; }
	virtual unsigned int getActiveWeapon(unsigned int weaponsetId, unsigned int levelsetId, unsigned int levelId) { return m_iActiveWeapon[weaponsetId][levelsetId][levelId]; }
	virtual unsigned int getActiveWeaponInCurrentSet(unsigned int levelId) { return m_iActiveWeapon[getActiveWeaponSet()][getActiveLevelSet()][levelId]; }
	virtual unsigned int getActiveLevelSet() { return m_iActiveLevelSet; }
	virtual const bool& getUnlockedWeaponSet(unsigned int setId) { return m_bUnlockedWeaponSets[setId]; }
	virtual const bool& getUnlockedWeapon(unsigned int setId, unsigned int weaponId) { return m_bUnlockedWeapons[setId][weaponId]; }
	virtual const bool& getUnlockedLevelSet(unsigned int setId) { return m_bUnlockedLevelSets[setId]; }
	virtual const bool& getUnlockedLevel(unsigned int setId, unsigned int levelId) { return m_bUnlockedLevels[setId][levelId]; }
	virtual std::vector<std::vector<std::vector<std::vector<Scorecard* > > > >& getScorecardArray() { return m_pScorecardArray; } // Returns the entire vector of vectors of vectors of scorecardsets for the player
	virtual Scorecard& getScorecard(unsigned int levelSetId, unsigned int levelId, unsigned int weaponSetId, unsigned int weaponId) { return *m_pScorecardArray[levelSetId][levelId][weaponSetId][weaponId]; } // Returns an individual scorecard
	virtual void printScorecardArray();
};