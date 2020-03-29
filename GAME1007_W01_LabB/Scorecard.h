#pragma once
#include <ostream>
#include "tinyxml2.h"
#include "DataSet.h"
using namespace tinyxml2;
// Class for holding all score info for a given level and weapon
class Scorecard
{
private:
	unsigned int m_iWeaponSetUsed;
	unsigned int m_iWeaponUsed;
	unsigned int m_iNumCollectibles;
	int m_iLeastTotalTime;
	int m_iLeastGroundTime;
	int m_totalTimeInAir;
	int m_totalLevelTime;
	int m_numShots;
	int m_numReloads;
	int m_numCoins;
	int m_levelCompleted;
	float m_fLowestGroundToTotalTimeRatio;
	int m_iFewestReloads;
	int m_iFewestShotsFired;
	float m_fLowestReloadsToShotsRatio;
	float m_fTopSpeed;
	unsigned int m_iNumberOfAttempts;
	unsigned int m_iNumberOfDeaths;
	unsigned int m_iNumberOfWins;
	float m_fLeastDeathsToWinRatio;
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode* pRoot;
	tinyxml2::XMLElement* pElement;

	// Private functions
	void setNumCollectibles(unsigned int num) { m_iNumCollectibles = num; }
public:
	// System functions
	Scorecard(unsigned int weaponset, unsigned int weapon, unsigned int numCollectibles);
	Scorecard(unsigned int weaponset, unsigned int weapon, unsigned int numCollectibles,
		int leastTotalTime, int leastGroundTime, float lowestGroundToTotal,
		int fewestReloads, int fewestShotsFired, float lowestReloadsToShots,
		unsigned int numDeaths, unsigned int numWins, float leastDeathsToWin, float topSpeed, unsigned int numAttempts);
	Scorecard(const Scorecard& ref);
	Scorecard(int complete, int totalTime, int airTime, int shots, int reloads,int coins);
	~Scorecard() {}

	// Mutator functions
	virtual void setLeastTotalTime(unsigned int time) { m_iLeastTotalTime = time; }
	virtual void setLeastGroundTime(unsigned int time) { m_iLeastGroundTime = time; }
	virtual void setLowestGroundToTotalTimeRatio(float ratio) { m_fLowestGroundToTotalTimeRatio = ratio; }
	virtual void setFewestReloads(unsigned int num) { m_iFewestReloads = num; }
	virtual void setFewestShotsFired(unsigned int num) { m_iFewestShotsFired = num; }
	virtual void setLowestReloadsToShotsRatio(float ratio) { m_fLowestReloadsToShotsRatio = ratio; }
	virtual void setTopSpeed(float speed) { m_fTopSpeed = speed; }
	virtual void setNumberOfAttempts(unsigned int num) { m_iNumberOfAttempts = num; }
	virtual void setNumberOfDeaths(unsigned int num) { m_iNumberOfDeaths = num; }
	virtual void setNumberOfWins(unsigned int num) { m_iNumberOfWins = num; }
	virtual void setLeastDeathsToWinRatio(float ratio) { m_fLeastDeathsToWinRatio = ratio; }
	virtual void setTotalLevelTime(int time) { m_totalLevelTime = time; }
	virtual void setTotalTimeInAir(int time) { m_totalTimeInAir = time; }
	virtual void setNumShots(int num) { m_numShots = num; }
	virtual void setNumReloads(int num) { m_numReloads = num; }
	virtual void setNumCoins(int num) { m_numCoins = num; }
	// Accessor functions
	virtual unsigned int getWeaponSetUsed() { return m_iWeaponSetUsed; }
	virtual unsigned int getWeaponUsed() { return m_iWeaponUsed; }
	virtual unsigned int getNumCollectibles() { return m_iNumCollectibles; }	// Total collectibles in the level
	virtual unsigned int getLeastTotalTime() { return m_iLeastTotalTime; }
	virtual unsigned int getLeastGroundTime() { return m_iLeastGroundTime; }
	virtual float getLeastGroundToTotalTimeRatio() { return m_fLowestGroundToTotalTimeRatio; }
	virtual unsigned int getFewestReloads() { return m_iFewestReloads; }
	virtual unsigned int getFewestShotsFired() { return m_iFewestShotsFired; }
	virtual float getLowestReloadsToShotsRatio () { return m_fLowestReloadsToShotsRatio; }
	virtual float getTopSpeed() { return m_fTopSpeed; }
	virtual unsigned int getNumberOfAttempts() { return m_iNumberOfAttempts; }
	virtual unsigned int getNumberOfDeaths() { return m_iNumberOfDeaths; }
	virtual unsigned int getNumberOfWins() { return m_iNumberOfWins; }
	virtual float getLeastDeathsToWinRatio() { return m_fLeastDeathsToWinRatio; }
	virtual int getTotalLevelTime() {return m_totalLevelTime ; }
	virtual int getTotalTimeInAir() {return m_totalTimeInAir ; }
	virtual int getNumShots() { return m_numShots; }
	virtual int getNumReloads() {return  m_numReloads; }
	virtual int getNumCoins() {return  m_numCoins; }
	// Overloaded operators
	inline Scorecard operator=(const Scorecard& rhs);	// Replaces all values of lhs with those of rhs
	inline Scorecard operator+=(const Scorecard& rhs);	// Replaces only the lower scores of lhs with those of rhs
	//inline Scorecard operator-=(const Scorecard& rhs);	// Replaces only the higher scores of lhs with those of rhs
	//inline bool operator<(const Scorecard& rhs);			// Checks if every single score of lhs is < than in rhs
	//inline bool operator>(const Scorecard& rhs);			// Checks if every single score of lhs is > than in rhs
	inline bool operator<=(const Scorecard& rhs);		// Checks if any single score of lhs is < than in rhs
	inline bool operator>=(const Scorecard& rhs);		// Checks if any single score of lhs is > than in rhs
	//inline bool operator==(const Scorecard& rhs);			// Checks if all scores of lhs are exactly == all of rhs
	//inline bool operator!=(const Scorecard& rhs);			// Checks if any single scores of lhs is different from rhs
	virtual void Print() { std::cout << this; }
	friend std::ostream& operator<<(std::ostream& os, Scorecard& ref);

	//Saving and Loading
	 void initXml();
	void saveData(int levelNum);
	void resetScores();
};

class LevelScore
{
private:
   
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLNode* pRoot;
	tinyxml2::XMLElement* pElement;
	friend class Scorecard;
public:
	std::vector<Scorecard*> m_vLevelsScores;
	LevelScore() { initXml(); }
	~LevelScore()=default;
	void initXml();
	void loadData();
};