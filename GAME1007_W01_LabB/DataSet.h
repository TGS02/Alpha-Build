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
	enum class Flags { NONE = 0, DEFAULT = 1, ALL = 2 };

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