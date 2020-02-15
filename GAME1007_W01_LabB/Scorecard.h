#pragma once
#include <ostream>
#include "DataSet.h"

// Class for holding all score info for a given level and weapon
class Scorecard
{
private:
	unsigned int m_iWeaponSetUsed;
	unsigned int m_iWeaponUsed;
	unsigned int m_iNumCollectibles;
	int m_iLeastTotalTime;
	int m_iLeastGroundTime;
	float m_fLowestGroundToTotalTimeRatio;
	int m_iFewestReloads;
	int m_iFewestShotsFired;
	float m_fLowestReloadsToShotsRatio;
	float m_fTopSpeed;
	unsigned int m_iNumberOfAttempts;
	unsigned int m_iNumberOfDeaths;
	unsigned int m_iNumberOfWins;
	float m_fLeastDeathsToWinRatio;

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
};
