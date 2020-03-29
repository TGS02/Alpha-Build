#include "Weapon.h"
#include "Engine.h"

void Weapon::Update()
{
	Uint32 delta = Engine::Instance().getDelta();
	if (m_iRefireCD < m_iRefireRate)
	{
		m_iRefireCD += delta;
		if (m_iRefireCD >= m_iRefireRate)
			std::cout << "Ready to fire again!" << std::endl;
	}
	if (m_iReloadCD < m_iReloadRate)
	{
		m_iReloadCD += delta;
		if (m_iReloadCD >= m_iReloadRate)
			std::cout << "Finished reloading!" << std::endl;
	}
}

bool Weapon::Fire()
{
	if (m_iShotsLeft > 0 && m_iRefireCD >= m_iRefireRate && m_iReloadCD >= m_iReloadRate)
	{
		--m_iShotsLeft;
		m_iRefireCD = 0;
		shotsLeft = shotsLeft - 1;
		frame = frame + 98;
		return true;
	}
	return false;
}

bool Weapon::Reload()
{
	if (m_iReloadsLeft > 0 && m_iReloadCD >= m_iReloadRate)
	{
		std::cout << "Reloading!" << std::endl;
		--m_iReloadsLeft;
		m_iReloadCD = 0;
		m_iShotsLeft = m_iMaxShots;
		shotsLeft = 6;
		frame = 0;
		return true;
	}
	return false;
}

void Weapon::Reset()
{
	m_iShotsLeft = m_iMaxShots;
	m_iReloadsLeft = m_iMaxReloads;
	m_iRefireCD = m_iRefireRate;
	m_iRefireRate = m_iReloadRate;
}

int Weapon::shotsGetter()
{
	return shotsLeft;
}

int Weapon::frameGetter()
{
	return frame;
}
