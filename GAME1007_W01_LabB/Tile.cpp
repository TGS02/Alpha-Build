#include "Tile.h"
#include "Engine.h"
#include "GameData.h"
#include "Util.h"

// Start of FrameSet
void FrameSet::clean()
{
	m_viTileId.clear();
	m_viTileId.shrink_to_fit();
	m_vpTex.clear();
	m_vpTex.shrink_to_fit();
	m_viAnimationRate.clear();
	m_viAnimationRate.shrink_to_fit();
}

void FrameSet::draw(SDL_Rect* src, SDL_Rect* dst)
{
	Engine::Instance().getCamera().RenderOffset(m_vpTex[m_iFrame], src, dst);
}

void FrameSet::update()
{
	animate();
}

void FrameSet::animate()
{
	if (m_vpTex.size() > 0 && m_viAnimationRate[m_iFrame] > 0) // If there are frames in the animation, and the animation timer for the given frame is not infinite
	{
		m_iAnimationCD += Engine::Instance().getDelta(); // Add delta time to the animation timer
		if (m_iAnimationCD >= m_viAnimationRate[m_iFrame]) // If the animation timer is now greater than the duration
		{
			m_iAnimationCD = m_iAnimationCD % m_viAnimationRate[m_iFrame]; // Reset the animation timer, keeping in mind the extra ticks leftover past the duration.
			m_iFrame++; // ... and iterate the frame counter
			if (m_iFrame >= m_vpTex.size()) // If the frame counter is now = the number of frames
			{
				m_iFrame = 0; // Reset it back to the start.
			}
		}
	}
}

void FrameSet::reset()
{
	m_iAnimationCD = 0;
	m_iFrame = 0;
}

void FrameSet::populateFrameSet(TileSet& tileset)
{
	m_vpTex.clear();
	m_vpTex.shrink_to_fit();
	for (int i = 0; i < m_viTileId.size(); i++)
	{
		m_vpTex.push_back(tileset.getDatum(m_viTileId[i])->getTexture());
	}
}
// End of FrameSet

// Start of CollidableFrameSet
void CollidableFrameSet::clean()
{
	m_vpfrCol.clear();
	m_vpfrCol.shrink_to_fit();
}

void CollidableFrameSet::animate()
{
	FrameSet::animate();

	unsigned int nextFrame = m_iFrame + 1;
	if (nextFrame >= m_viTileId.size())
	{
		nextFrame = 0;
	}

	if (m_viAnimationRate[m_iFrame] != 0)
	{
		float t = static_cast<float>(m_iAnimationCD) / static_cast<float>(m_viAnimationRate[m_iFrame]);
		m_pfrCol.x = Util::lerp(m_vpfrCol[m_iFrame].x, m_vpfrCol[nextFrame].x, t);
		m_pfrCol.y = Util::lerp(m_vpfrCol[m_iFrame].y, m_vpfrCol[nextFrame].y, t);
		m_pfrCol.w = Util::lerp(m_vpfrCol[m_iFrame].w, m_vpfrCol[nextFrame].w, t);
		m_pfrCol.h = Util::lerp(m_vpfrCol[m_iFrame].h, m_vpfrCol[nextFrame].h, t);
	}
}

void CollidableFrameSet::populateFrameSet(TileSet& tileset)
{
	FrameSet::populateFrameSet(tileset);
	m_vpfrCol.clear();
	m_vpfrCol.shrink_to_fit();
	m_vbCollidable.clear();
	m_vbCollidable.shrink_to_fit();
	for (int i = 0; i < m_viTileId.size(); i++)
	{
		CollidableTile* collidableTile = dynamic_cast<CollidableTile*>(tileset.getDatum(m_viTileId[i]));
		if (collidableTile != nullptr)
		{
			SDL_FRect colToAdd = collidableTile->getFCol();
			bool boolToAdd = collidableTile->getCollidable();
			m_vpfrCol.push_back(colToAdd);
			m_vbCollidable.push_back(boolToAdd);
		}
	}
	m_pfrCol = m_vpfrCol[0];
}
// End of CollidableFrameSet

// Start of Tile
void Tile::clean()
{
	delete m_FrameSet;
}

void Tile::draw()
{
	if (SDL_HasIntersection(&Engine::Instance().getCamera().getDst(), &m_dst))
	{
		if (m_FrameSet != nullptr) // If there is even a single frame of 'animation', the tile's own texture will never get rendered.
		{
			m_FrameSet->draw(&m_src, &m_dst);
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
	if (m_FrameSet != nullptr)
	{
		m_FrameSet->animate();
	}
}

void Tile::reset()
{
	if (m_FrameSet != nullptr)
	{
		m_FrameSet->reset();
	}
}

void Tile::setFrameSet(FrameSet* frameSet)
{
	if (m_FrameSet != nullptr)
	{
		delete m_FrameSet;
		m_FrameSet = nullptr;
	}
	m_FrameSet = frameSet;
}
// End of Tile

// Start of CollidableTile
SDL_FRect CollidableTile::getFCol()
{
	SDL_Rect idst = getDst();
	SDL_FRect fdst = { static_cast<float>(idst.x), static_cast<float>(idst.h), static_cast<float>(idst.w), static_cast<float>(idst.h) };
	SDL_FRect colrect = m_frCol;

	CollidableFrameSet* colset = nullptr;
	if (m_FrameSet != nullptr)
	{
		colset = dynamic_cast<CollidableFrameSet*>(m_FrameSet);
	}

	if (colset != nullptr)
	{
		SDL_FRect fcol = colset->getFCol();
		colrect = { fdst.x + fcol.x, fdst.y + fcol.y, fcol.w, fcol.h };
	}
	else
	{
		colrect = { fdst.x + m_frCol.x, fdst.y + m_frCol.y, m_frCol.w, m_frCol.h };
	}

	return colrect;
}

SDL_Rect CollidableTile::getICol()
{
	SDL_Rect idst = getDst();
	SDL_Rect icol = { static_cast<int>(m_frCol.x), static_cast<int>(m_frCol.y), static_cast<int>(m_frCol.w), static_cast<int>(m_frCol.h) };
	SDL_Rect colrect = icol;

	CollidableFrameSet* colset = nullptr;
	if (m_FrameSet != nullptr)
	{
		colset = dynamic_cast<CollidableFrameSet*>(m_FrameSet);
	}

	if (colset != nullptr)
	{
		SDL_FRect fcol = colset->getFCol();
		colrect = { idst.x + static_cast<int>(fcol.x), idst.y + static_cast<int>(fcol.y), static_cast<int>(fcol.w), static_cast<int>(fcol.h) };
	}
	else
	{
		colrect = { idst.x + icol.x, idst.y + icol.y, icol.w, icol.h };
	}

	return colrect;
}
// End of CollidableTile

// Start of InteractiveTile
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
// End of InteractiveTile
