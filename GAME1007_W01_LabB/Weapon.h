#pragma once
#include <string>
#include <SDL.h>

class Weapon
{
private:
	// Weapon metadata
	unsigned int m_iId;
	std::string m_strName;

	// Weapon stats
	float m_fRecoilForce;
	Uint32 m_iRefireRate;
	Uint32 m_iReloadRate;
	unsigned int m_iMaxShots;
	unsigned int m_iMaxReloads;

	// ammo ui info
	int shotsLeft = 6;
	int frame = 0;

	// Player stats
	Uint32 m_iRefireCD;
	Uint32 m_iReloadCD;
	unsigned int m_iShotsLeft;
	unsigned int m_iReloadsLeft;

	// Private functions
	virtual void setId(unsigned int id) { m_iId = id; }
	virtual void setName(std::string name) { m_strName = name; }
public:
	// System functions
	Weapon(unsigned int id, std::string name, float recoil, unsigned int refireRate, unsigned int reloadRate, unsigned int maxShots, unsigned int maxReloads) :
		m_iId(id), m_strName(name), m_fRecoilForce(recoil), m_iRefireRate(static_cast<Uint32>(refireRate)), m_iReloadRate(static_cast<Uint32>(reloadRate)), m_iMaxShots(maxShots), m_iMaxReloads(maxReloads),
		m_iRefireCD(static_cast<Uint32>(refireRate)), m_iReloadCD(static_cast<Uint32>(reloadRate)), m_iShotsLeft(maxShots), m_iReloadsLeft(maxReloads) {}
	~Weapon() {}

	// Mutator functions
	virtual void setRecoilForce(float recoil) { m_fRecoilForce = recoil; }
	virtual void setRefireRate(Uint32 rate) { m_iRefireRate = rate; }
	virtual void setReloadRate(Uint32 rate) { m_iReloadRate = rate; }
	virtual void setMaxShots(unsigned int num) { m_iMaxShots = num; }
	virtual void setMaxReloads(unsigned int num) { m_iMaxReloads = num; }
	virtual void setRefireCD(Uint32 cd = 0) { m_iRefireCD = cd; }
	virtual void setReloadCD(Uint32 cd = 0) { m_iReloadCD = cd; }
	virtual void setShotsLeft(unsigned int num) { m_iShotsLeft = num; }
	virtual void setReloadsLeft(unsigned int num) { m_iReloadsLeft = num; }

	// Accessor functions
	virtual unsigned int getId() { return m_iId; }
	virtual std::string getName() { return m_strName; }
	virtual float getRecoilForce() { return m_fRecoilForce; }
	virtual Uint32 getRefireRate() { return m_iRefireRate; }
	virtual Uint32 getReloadRate() { return m_iReloadRate; }
	virtual unsigned int getMaxShots() { return m_iMaxShots; }
	virtual unsigned int getMaxReloads() { return m_iMaxReloads; }
	virtual Uint32 getRefireCD() { return m_iRefireCD; }
	virtual Uint32 getReloadCD() { return m_iReloadCD; }
	virtual unsigned int getShotsLeft() { return m_iShotsLeft; }
	virtual unsigned int getReloadsLeft() { return m_iReloadsLeft; }

	// Gameplay functions
	virtual void Update();
	virtual bool Fire();
	virtual bool Reload();
	virtual void Reset();
	int shotsGetter();
	int frameGetter();
};

