#pragma once
#include <string>

class Weapon
{
private:
	// Weapon metadata
	unsigned int m_iId;
	std::string m_strName;

	// Weapon stats
	float m_fRecoilForce;
	float m_fRefireRate;
	float m_fReloadRate;
	unsigned int m_iMaxShots;
	unsigned int m_iMaxReloads;

	// Player stats
	float m_fRefireCD;
	float m_fReloadCD;
	unsigned int m_iShotsLeft;
	unsigned int m_iReloadsLeft;

	// Private functions
	virtual void setId(unsigned int id) { m_iId = id; }
	virtual void setName(std::string name) { m_strName = name; }
public:
	// System functions
	Weapon(unsigned int id, std::string name, float recoil, float refireRate, float reloadRate, unsigned int maxShots, unsigned int maxReloads) : 
		m_iId(id), m_strName(name), m_fRecoilForce(recoil), m_fRefireRate(refireRate), m_fReloadRate(reloadRate), m_iMaxShots(maxShots), m_iMaxReloads(maxReloads),
		m_fRefireCD(refireRate), m_fReloadCD(reloadRate), m_iShotsLeft(maxShots), m_iReloadsLeft(maxReloads) {}
	~Weapon() {}

	// Mutator functions
	virtual void setRecoilForce(float recoil) { m_fRecoilForce = recoil; }
	virtual void setRefireRate(float rate) { m_fRefireRate = rate; }
	virtual void setReloadRate(float rate) { m_fReloadRate = rate; }
	virtual void setMaxShots(unsigned int num) { m_iMaxShots = num; }
	virtual void setMaxReloads(unsigned int num) { m_iMaxReloads = num; }
	virtual void setRefireCD(float cd = 0) { m_fRefireCD = cd; }
	virtual void setReloadCD(float cd = 0) { m_fReloadCD = cd; }
	virtual void setShotsLeft(unsigned int num) { m_iShotsLeft = num; }
	virtual void setReloadsLeft(unsigned int num) { m_iReloadsLeft = num; }

	// Accessor functions
	virtual unsigned int getId() { return m_iId; }
	virtual std::string getName() { return m_strName; }
	virtual float getRecoilForce() { return m_fRecoilForce; }
	virtual float getRefireRate() { return m_fRefireRate; }
	virtual float geteloadRate() { return m_fReloadRate; }
	virtual unsigned int getMaxShots() { return m_iMaxShots; }
	virtual unsigned int getMaxReloads() { return m_iMaxReloads; }
	virtual float getRefireCD() { return m_fRefireCD; }
	virtual float getReloadCD() { return m_fReloadCD; }
	virtual unsigned int getShotsLeft() { return m_iShotsLeft; }
	virtual unsigned int getReloadsLeft() { return m_iReloadsLeft; }

	// Gameplay functions
	virtual void Fire() {}
	virtual void Reload() {}
};
