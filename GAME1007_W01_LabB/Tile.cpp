#include "Tile.h"
#include "Engine.h"
#include "GameData.h"

void Tile::draw()
{
	if (SDL_HasIntersection(&Engine::Instance().getCamera().getDst(), &m_dst))
	{
		if (m_FrameSet.size() > 0)
		{
			// If there is even a single frame of 'animation', the tile's own texture will never get rendered.
			Engine::Instance().getCamera().RenderOffset(m_FrameSet[m_iFrame], &m_src, &m_dst);
		}
		else
		{
			Engine::Instance().getCamera().RenderOffset(m_pTex, &m_src, &m_dst);
			//TextureManager::Draw(Engine::Instance().GetRenderer(), m_pTex, &m_src, &m_dst);
		}
	}
}

void Tile::update()
{
	animate();
}

void Tile::animate()
{
	if (m_FrameSet.size() > 0 && m_iAnimationMax[m_iFrame] > 0) // If there are frames in the animation, and the animation timer for the given frame is not infinite
	{
		m_iAnimationCD += Engine::Instance().getDelta(); // Add delta time to the animation timer
		if (m_iAnimationCD >= m_iAnimationMax[m_iFrame]) // If the animation timer is now greater than the duration
		{
			m_iAnimationCD = m_iAnimationCD % m_iAnimationMax[m_iFrame]; // Reset the animation timer, keeping in mind the extra ticks leftover past the duration.
			m_iFrame++; // ... and iterate the frame counter
			if (m_iFrame >= m_FrameSet.size()) // If the frame counter is now = the number of frames
			{
				m_iFrame = 0; // Reset it back to the start.
			}
		}
	}
}

void Tile::reset()
{
	m_iAnimationCD = 0;
	m_iFrame = 0;
}

void Tile::populateFrameSet(DataSet_1D<Tile>& tileset)
{
	m_FrameSet.clear();
	m_FrameSet.shrink_to_fit();
	for (unsigned int i = 0; i < m_iFrameSet.size(); i++)
	{
		unsigned int index = m_iFrameSet[i];
		m_FrameSet.push_back(tileset.getDatum(index)->getTexture());
	}
}

void InteractiveTile::draw()
{
	if (m_VanishOnInteraction != true || m_VanishOnInteraction == true && m_interacted == false)
	{
		Tile::draw();
	}
}

void InteractiveTile::update()
{
	animate();
}

void InteractiveTile::animate()
{
	if (m_AnimateOnInteraction)
	{
		if (m_interacted)
		{
			Tile::animate();
		}
	}
	else
	{
		Tile::animate();
	}
}

void InteractiveTile::reset()
{
	m_interacted = false;
	Tile::reset();
}
