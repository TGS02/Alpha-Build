#include <iomanip>
#include "tinyxml2.h"
#include "Scorecard.h"

Scorecard::Scorecard(unsigned int levelset, unsigned int level, unsigned int weaponset, unsigned int weapon, unsigned int numCollectables,
	int leastTotalTime, int leastGroundTime, float lowestGroundToTotal,
	int fewestReloads, int fewestShotsFired, float lowestReloadsToShots,
	unsigned int numDeaths, unsigned int numWins, float leastDeathsToWin, float topSpeed, unsigned int numAttempts)
	: m_iWeaponSetUsed(weaponset), m_iWeaponUsed(weapon), m_iNumCollectables(numCollectables),
	m_iLeastTotalTime(leastTotalTime), m_iLeastGroundTime(leastGroundTime), m_fLowestGroundToTotalTimeRatio(lowestGroundToTotal),
	m_iFewestReloads(fewestReloads), m_iFewestShotsFired(fewestShotsFired), m_fLowestReloadsToShotsRatio(lowestReloadsToShots),
	m_iNumberOfDeaths(numDeaths), m_iNumberOfWins(numWins), m_fLeastDeathsToWinRatio(leastDeathsToWin),
	m_fTopSpeed(topSpeed), m_iNumberOfAttempts(numAttempts) {}

Scorecard::Scorecard(const Scorecard& ref) :
	m_iWeaponSetUsed(ref.m_iWeaponSetUsed),
	m_iWeaponUsed(ref.m_iWeaponUsed),
	m_iNumCollectables(ref.m_iNumCollectables),
	m_iLeastTotalTime(ref.m_iLeastTotalTime),
	m_iLeastGroundTime(ref.m_iLeastGroundTime),
	m_fLowestGroundToTotalTimeRatio(ref.m_fLowestGroundToTotalTimeRatio),
	m_iFewestReloads(ref.m_iFewestReloads),
	m_iFewestShotsFired(ref.m_iFewestShotsFired),
	m_fLowestReloadsToShotsRatio(ref.m_fLowestReloadsToShotsRatio),
	m_fTopSpeed(ref.m_fTopSpeed),
	m_iNumberOfAttempts(ref.m_iNumberOfAttempts),
	m_iNumberOfDeaths(ref.m_iNumberOfDeaths),
	m_iNumberOfWins(ref.m_iNumberOfWins),
	m_fLeastDeathsToWinRatio(ref.m_fLeastDeathsToWinRatio) {}





/*--------------------------
	Overloaded Operators
--------------------------*/

//// Replaces all values of lhs with those of rhs
//inline Scorecard Scorecard::operator=(const Scorecard& rhs)
//{
//	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectables != rhs.m_iNumCollectables)
//	{
//		std::cout << "Attempted to perform binary operation on incomparible Scorecards." << std::endl;
//	}
//	else
//	{
//		this->m_iLeastTotalTime = rhs.m_iLeastTotalTime;
//		this->m_iLeastGroundTime = rhs.m_iLeastGroundTime;
//		this->m_fLowestGroundToTotalTimeRatio = rhs.m_fLowestGroundToTotalTimeRatio;
//		this->m_iFewestReloads = rhs.m_iFewestReloads;
//		this->m_iFewestShotsFired = rhs.m_iFewestShotsFired;
//		this->m_fLowestReloadsToShotsRatio = rhs.m_fLowestReloadsToShotsRatio;
//		this->m_fTopSpeed = rhs.m_fTopSpeed;
//		this->m_iNumberOfAttempts = rhs.m_iNumberOfAttempts;
//		this->m_iNumberOfDeaths = rhs.m_iNumberOfDeaths;
//		this->m_iNumberOfWins = rhs.m_iNumberOfWins;
//		this->m_fLeastDeathsToWinRatio = rhs.m_fLeastDeathsToWinRatio;
//	}
//	return *this;
//}

//// Replaces only the lower scores of lhs with those of rhs
//inline Scorecard Scorecard::operator+=(const Scorecard& rhs)
//{
//	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectables != rhs.m_iNumCollectables)
//	{
//		std::cout << "Attempted to perform binary operation on incomparible Scorecards." << std::endl;
//	}
//	else
//	{
//		if (this->m_iLeastTotalTime < rhs.m_iLeastTotalTime)
//			this->m_iLeastTotalTime = rhs.m_iLeastTotalTime;
//		if (this->m_iLeastGroundTime < rhs.m_iLeastGroundTime)
//			this->m_iLeastGroundTime = rhs.m_iLeastGroundTime;
//		if (this->m_fLowestGroundToTotalTimeRatio < rhs.m_fLowestGroundToTotalTimeRatio)
//			this->m_fLowestGroundToTotalTimeRatio = rhs.m_fLowestGroundToTotalTimeRatio;
//		if (this->m_iFewestReloads < rhs.m_iFewestReloads)
//			this->m_iFewestReloads = rhs.m_iFewestReloads;
//		if (this->m_iFewestShotsFired < rhs.m_iFewestShotsFired)
//			this->m_iFewestShotsFired = rhs.m_iFewestShotsFired;
//		if (this->m_fLowestReloadsToShotsRatio < rhs.m_fLowestReloadsToShotsRatio)
//			this->m_fLowestReloadsToShotsRatio = rhs.m_fLowestReloadsToShotsRatio;
//		if (this->m_fTopSpeed < rhs.m_fTopSpeed)
//			this->m_fTopSpeed = rhs.m_fTopSpeed;
//		if (this->m_iNumberOfAttempts < rhs.m_iNumberOfAttempts)
//			this->m_iNumberOfAttempts = rhs.m_iNumberOfAttempts;
//		if (this->m_iNumberOfDeaths < rhs.m_iNumberOfDeaths)
//			this->m_iNumberOfDeaths = rhs.m_iNumberOfDeaths;
//		if (this->m_iNumberOfWins < rhs.m_iNumberOfWins)
//			this->m_iNumberOfWins = rhs.m_iNumberOfWins;
//		if (this->m_fLeastDeathsToWinRatio < rhs.m_fLeastDeathsToWinRatio)
//			this->m_fLeastDeathsToWinRatio = rhs.m_fLeastDeathsToWinRatio;
//	}
//	return *this;
//}

// Checks if any single score of lhs is < than in rhs
inline bool Scorecard::operator<=(const Scorecard& rhs)
{
	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectables != rhs.m_iNumCollectables)
	{
		std::cout << "Attempted to perform binary operation on incomparible Scorecards." << std::endl;
	}
	else
	{
		if (this->m_iLeastTotalTime < rhs.m_iLeastTotalTime)
			return true;
		if (this->m_iLeastGroundTime < rhs.m_iLeastGroundTime)
			return true;
		if (this->m_fLowestGroundToTotalTimeRatio < rhs.m_fLowestGroundToTotalTimeRatio)
			return true; 
		if (this->m_iFewestReloads < rhs.m_iFewestReloads)
			return true;
		if (this->m_iFewestShotsFired < rhs.m_iFewestShotsFired)
			return true; 
		if (this->m_fLowestReloadsToShotsRatio < rhs.m_fLowestReloadsToShotsRatio)
			return true;
		if (this->m_fTopSpeed < rhs.m_fTopSpeed)
			return true; 
		if (this->m_iNumberOfAttempts < rhs.m_iNumberOfAttempts)
			return true; 
		if (this->m_iNumberOfDeaths < rhs.m_iNumberOfDeaths)
			return true; 
		if (this->m_iNumberOfWins < rhs.m_iNumberOfWins)
			return true; 
		if (this->m_fLeastDeathsToWinRatio < rhs.m_fLeastDeathsToWinRatio)
			return true; 
	}
	return false;
}
// Checks if any single score of lhs is > than in rhs
inline bool Scorecard::operator>=(const Scorecard& rhs)
{
	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectables != rhs.m_iNumCollectables)
	{
		std::cout << "Attempted to perform binary operation on incomparible Scorecards." << std::endl;
	}
	else
	{
		if (this->m_iLeastTotalTime > rhs.m_iLeastTotalTime)
			return true;
		if (this->m_iLeastGroundTime > rhs.m_iLeastGroundTime)
			return true;
		if (this->m_fLowestGroundToTotalTimeRatio > rhs.m_fLowestGroundToTotalTimeRatio)
			return true;
		if (this->m_iFewestReloads > rhs.m_iFewestReloads)
			return true;
		if (this->m_iFewestShotsFired > rhs.m_iFewestShotsFired)
			return true;
		if (this->m_fLowestReloadsToShotsRatio > rhs.m_fLowestReloadsToShotsRatio)
			return true;
		if (this->m_fTopSpeed > rhs.m_fTopSpeed)
			return true;
		if (this->m_iNumberOfAttempts > rhs.m_iNumberOfAttempts)
			return true;
		if (this->m_iNumberOfDeaths > rhs.m_iNumberOfDeaths)
			return true;
		if (this->m_iNumberOfWins > rhs.m_iNumberOfWins)
			return true;
		if (this->m_fLeastDeathsToWinRatio > rhs.m_fLeastDeathsToWinRatio)
			return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, Scorecard& ref)
{
	using namespace std;
	const string ____WeaponSet = "Weapon Set";
	const string _______Weapon = "Weapon Used";
	const string ________NumCs = "Collectibles";
	const string ____TotalTime = "Least Total Time";
	const string ___GroundTime = "Least Ground Time";
	const string _Ground_Total = "Lowest Ground:Total";
	const string ______Reloads = "Fewest Reloads";
	const string ________Shots = "Fewest Shots Fired";
	const string Reloads_Shots = "Fewest Reloads:Shots";
	const string _______Deaths = "Number of Deaths";
	const string _________Wins = "Number of Wins";
	const string ___Deaths_Win = "Least Deaths:Win";
	const string _____TopSpeed = "Top Speed";
	const string _____Attempts = "Total Attempts";
	os << setw(25) << right << ____WeaponSet << setw(2) << ": " << setw(8) << left << ref.getWeaponSetUsed();
	os << setw(25) << right << _______Weapon << setw(2) << ": " << setw(8) << left << ref.getWeaponUsed();
	os << setw(25) << right << ________NumCs << setw(2) << ": " << setw(8) << left << ref.getNumCollectables() << endl;
	os << setw(25) << right << ____TotalTime << setw(2) << ": " << setw(8) << left << ref.getLeastTotalTime();
	os << setw(25) << right << ___GroundTime << setw(2) << ": " << setw(8) << left << ref.getLeastGroundTime();
	os << setw(25) << right << _Ground_Total << setw(2) << ": " << setw(8) << left << ref.getLeastGroundToTotalTimeRatio() << endl;
	os << setw(25) << right << ______Reloads << setw(2) << ": " << setw(8) << left << ref.getFewestReloads();
	os << setw(25) << right << ________Shots << setw(2) << ": " << setw(8) << left << ref.getFewestShotsFired();
	os << setw(25) << right << Reloads_Shots << setw(2) << ": " << setw(8) << left << ref.getLowestReloadsToShotsRatio() << endl;
	os << setw(25) << right << _______Deaths << setw(2) << ": " << setw(8) << left << ref.getNumberOfDeaths();
	os << setw(25) << right << _________Wins << setw(2) << ": " << setw(8) << left << ref.getNumberOfWins();
	os << setw(25) << right << ___Deaths_Win << setw(2) << ": " << setw(8) << left << ref.getLeastDeathsToWinRatio() << endl;
	os << setw(25) << right << _____TopSpeed << setw(2) << ": " << setw(8) << left << ref.getTopSpeed();
	os << setw(25) << right << _____Attempts << setw(2) << ": " << setw(8) << left << ref.getNumberOfAttempts() << endl;
	return os;
}
