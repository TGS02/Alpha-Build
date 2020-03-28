#include <iomanip>
#include "tinyxml2.h"
#include "Scorecard.h"

Scorecard::Scorecard(unsigned int weaponset, unsigned int weapon, unsigned int numCollectibles)
	: m_iWeaponSetUsed(weaponset), m_iWeaponUsed(weapon), m_iNumCollectibles(numCollectibles)
{
	initXml();
}

Scorecard::Scorecard(unsigned int weaponset, unsigned int weapon, unsigned int numCollectibles, int leastTotalTime, int leastGroundTime, float lowestGroundToTotal, int fewestReloads, int fewestShotsFired, float lowestReloadsToShots, unsigned int numDeaths, unsigned int numWins, float leastDeathsToWin, float topSpeed, unsigned int numAttempts)
	: m_iWeaponSetUsed(weaponset), m_iWeaponUsed(weapon), m_iNumCollectibles(numCollectibles),
	m_iLeastTotalTime(leastTotalTime), m_iLeastGroundTime(leastGroundTime), m_fLowestGroundToTotalTimeRatio(lowestGroundToTotal),
	m_iFewestReloads(fewestReloads), m_iFewestShotsFired(fewestShotsFired), m_fLowestReloadsToShotsRatio(lowestReloadsToShots),
	m_iNumberOfDeaths(numDeaths), m_iNumberOfWins(numWins), m_fLeastDeathsToWinRatio(leastDeathsToWin),
	m_fTopSpeed(topSpeed), m_iNumberOfAttempts(numAttempts)
{
	initXml();
}

Scorecard::Scorecard(const Scorecard& ref) :
	m_iWeaponSetUsed(ref.m_iWeaponSetUsed),
	m_iWeaponUsed(ref.m_iWeaponUsed),
	m_iNumCollectibles(ref.m_iNumCollectibles),
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
	m_fLeastDeathsToWinRatio(ref.m_fLeastDeathsToWinRatio)
{
	initXml();
}

Scorecard::Scorecard(int complete, int totalTime, int airTime, int shots, int reloads, int coins)
	:m_levelCompleted(complete),m_totalLevelTime(totalTime),m_totalTimeInAir(airTime), m_numShots(shots)
	,m_numReloads(reloads), m_numCoins(coins)
{
	initXml();
}


/*--------------------------
	Overloaded Operators
--------------------------*/

//// Replaces all values of lhs with those of rhs
//inline Scorecard Scorecard::operator=(const Scorecard& rhs)
//{
//	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectibles != rhs.m_iNumCollectibles)
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
//	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectibles != rhs.m_iNumCollectibles)
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
	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectibles != rhs.m_iNumCollectibles)
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
	if (this->m_iWeaponSetUsed != rhs.m_iWeaponSetUsed || this->m_iWeaponUsed != rhs.m_iWeaponUsed || this->m_iNumCollectibles != rhs.m_iNumCollectibles)
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
	os << setw(25) << right << ________NumCs << setw(2) << ": " << setw(8) << left << ref.getNumCollectibles() << endl;
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

void Scorecard::initXml()
{
	/*XMLDocument xmlDoc;
		XMLNode* pRoot = xmlDoc.NewElement("playerdataset");
		xmlDoc.InsertEndChild(pRoot);
		XMLElement* pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 0);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 1);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 2);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 3);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 4);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 5);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 6);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		pElement = xmlDoc.NewElement("Level");
		pElement->SetAttribute("id", 7);
		pElement->SetAttribute("complete", 0);
		pElement->SetAttribute("timeInLevel", 0);
		pElement->SetAttribute("TimeInAir", 0);
		pElement->SetAttribute("NumberOfShotsFired", 0);
		pElement->SetAttribute("NumberOfReloadsUsed", 0);
		pElement->SetAttribute("NumberOfCoinsCollected", 0);
		pRoot->InsertEndChild(pElement);
		xmlDoc.SaveFile("LevelScores.xml");*/
	if(xmlDoc.LoadFile("LevelScores.xml")!=0)
	{
		xmlDoc.PrintError();
	}
	pRoot = xmlDoc.FirstChildElement("playerdataset");
}

void LevelScore::initXml()
{
	xmlDoc.LoadFile("LevelScores.xml");
	pRoot = xmlDoc.FirstChildElement("playerdataset");
}

void LevelScore::loadData()
{
	if (!m_vLevelsScores.empty())
		m_vLevelsScores.clear();
	pRoot = xmlDoc.FirstChildElement("playerdataset");
	//	pElement = pRoot->FirstChildElement("player");
	pElement = pRoot->FirstChildElement("Level");

	int complete, totalTime, airTime, shots, reloads, coins;
		while (pElement != nullptr)
	{

		
		pElement->QueryIntAttribute("complete",				  &complete);
		pElement->QueryIntAttribute("timeInLevel",			  &totalTime);
		pElement->QueryIntAttribute("TimeInAir",		      &airTime);
		pElement->QueryIntAttribute("NumberOfShotsFired",     &shots);
		pElement->QueryIntAttribute("NumberOfReloadsUsed",    &reloads);
		pElement->QueryIntAttribute("NumberOfCoinsCollected", &coins);


		m_vLevelsScores.push_back(new Scorecard(complete,totalTime,airTime,shots,reloads,coins));
		pElement = pElement->NextSiblingElement("Level");

	}
}

void Scorecard::saveData(int levelNum)
{
	pRoot = xmlDoc.FirstChildElement("playerdataset");
//	pElement = pRoot->FirstChildElement("player");
	pElement = pRoot->FirstChildElement("Level");

	int level;
	pElement->QueryIntAttribute("id", &level);

	while (level != levelNum)
	{
		pElement = pElement->NextSiblingElement("Level");
		pElement->QueryIntAttribute("id", &level);
	}
	pElement->SetAttribute("id", levelNum);
	pElement->SetAttribute("complete", 1);
	pElement->SetAttribute("timeInLevel", m_totalLevelTime);
	pElement->SetAttribute("TimeInAir", m_totalTimeInAir);
	pElement->SetAttribute("NumberOfShotsFired", m_numShots);
	pElement->SetAttribute("NumberOfReloadsUsed", m_numReloads);
	pElement->SetAttribute("NumberOfCoinsCollected", m_numCoins);

	xmlDoc.SaveFile("LevelScores.xml");
}

void Scorecard::resetScores()
{
	m_numCoins = 0;
}

