#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2.h"

class DataSet
{
private:
	unsigned int m_iId;
	std::string m_strName;
	std::string m_strFileName;
public:
	// Class enumerations
	/*For now: Pass ALL and DEFAULT_FROMISTREAM to switch to a single new player.
	* NONE = 0, un/load nothing (add any new players to the next indices of the set)
	* DEFAULT = 1, un/load a specific player (shift the set, following the deleted player, one index lower, then add any new players to the next indices of the set)
	* ALL = 2, un/load all players in the PlayerData file (clear the entire set)
	* FROMISTREAM = 4, input the player's name from the istream*/
	enum class Flags { NONE = 0, DEFAULT = 1, ALL = 2, FROMISTREAM = 4, DEFAULT_FROMISTREAM = 5 };

	// System functions
	DataSet(unsigned int id, std::string name, std::string filename) : m_iId(id), m_strName(name), m_strFileName(filename) {}
	virtual bool LoadFromXML(Flags unloadFlags = Flags::ALL, Flags loadFlags = Flags::ALL) = 0;
	virtual bool SaveToXML(Flags flags = Flags::ALL) { return false; }
	virtual void Clean(Flags flags = Flags::ALL) = 0;

	// Mutator functions
	virtual void setId(unsigned int id) { m_iId = id; }
	virtual void setName(std::string name) { m_strName = name; }

	// Accessor functions
	virtual unsigned int getId() { return m_iId; }
	virtual std::string getName() { return m_strName; }
	virtual std::string getFileName() { return m_strFileName; }
	virtual void printFileName(std::string callingClass) { std::cout << getFileName() << std::endl; }
};

template <class T>
class DataSet_1D :
	public DataSet
{
private:
	std::vector<std::string> m_pDataFileSet;
	std::vector<T*> m_pDataSet;
public:
	// System functions
	DataSet_1D(unsigned int id, std::string name, std::string filename) : DataSet(id, name, filename) {}
	~DataSet_1D() { Clean(); }
	virtual bool LoadFromXML(Flags unloadFlags = Flags::ALL, Flags loadFlags = Flags::ALL);
	virtual void Clean(Flags unloadFlags = Flags::ALL);

	// Mutator functions
	//virtual void InitDatum(unsigned int index, T ref) { m_pDataSet[index].push_Back(T(ref)); }

	// Accessor functions
	std::string getDataFileName(unsigned int index) { return m_pDataFileSet[index]; }
	std::vector<T*>* getDataSet() { return &m_pDataSet; }
	T* getDatum(unsigned int index) { return m_pDataSet[index]; }

	// Overloaded operators
	//friend std::ostream& operator<<(std::ostream& os, DataSet_1D<T>& ref);
};

template <class T>
class DataSet_2D :
	public DataSet
{
private:
	unsigned int m_iId_y;
	unsigned int m_iId_z;
	std::vector<std::vector<T*>*> m_pDataSet; // This 2D array stores Scorecard pointers by [weapon][collectible].
public:
	// System functions
	DataSet_2D(unsigned int xId, unsigned int yId, unsigned int zId, std::string name, std::string filename) : DataSet(xId, name, filename), m_iId_y(yId), m_iId_z(xId) {}
	~DataSet_2D() { Clean(); }
	virtual bool LoadFromXML(Flags unloadFlags = Flags::ALL, Flags loadFlags = Flags::ALL);
	virtual void Clean(Flags flags = Flags::ALL);

	// Mutator functions
	//virtual void setDataSet_x(unsigned int numweapons) { m_pDataSet = new T * *[numweapons]; }
	//virtual void setDataSet_y(unsigned int weapon, unsigned int numcollectibles) { m_pDataSet[weapon] = new T * [numcollectibles]; }
	//virtual void setDatum(unsigned int weaponset, unsigned int weapon, unsigned int collectible) { delete m_pDataSet[weapon][collectible]; m_pDataSet[weapon][collectible] = new T(weaponset, weapon, collectible); }
	//virtual void updateScorecard(unsigned int weaponIndex, unsigned int collectibleIndex, const Scorecard& ref) { *m_pDataSet[weaponIndex][collectibleIndex] += ref; }

	// Accessor functions
	unsigned int getId_y() { return m_iId_y; }
	unsigned int getId_z() { return m_iId_z; }
	T* getDatum(unsigned int weaponIndex, unsigned int collectibleIndex) { return m_pDataSet[weaponIndex]->at(collectibleIndex); }
	void Print();

	// Overloaded operators
	//friend std::ostream& operator<<(std::ostream& os, DataSet_2D<T>& ref);
};

//template <class T>
//std::ostream& operator<<(std::ostream& os, DataSet_2D<T>& ref)
//{
//	std::cerr << "ERROR: ostream overload function not defined." << std::endl;
//}

//std::ostream& operator<<(std::ostream& os, DataSet_2D<Scorecard>& ref)
//{
//	std::cerr << "ERROR: ostream overload function not defined." << std::endl;
//	//const std::string _ScorecardSet = "Scorecard Set";
//	//const std::string _Scorecard = "Scorecard";
//
//	//os << _ScorecardSet << ": " << ref.getId() << std::endl;
//	//for (unsigned int weaponIndex = 0; weaponIndex < ref.getNumData_x(); weaponIndex++)
//	//{
//	//	for (unsigned int collectibleIndex = 0; collectibleIndex < ref.getNumData_y(weaponIndex); collectibleIndex++)
//	//	{
//	//		os << _Scorecard << ": " << weaponIndex << "-" << collectibleIndex << std::endl;
//	//		//os << ref.getDatum(weaponIndex, collectibleIndex);
//	//	}
//	//}
//	return os;
//}
