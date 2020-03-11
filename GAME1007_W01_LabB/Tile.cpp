#include "Tile.h"
#include "Engine.h"

void Tile::draw()
{
	if (SDL_HasIntersection(&Engine::Instance().getCamera().getDst(), &m_irDst))
	{
		Engine::Instance().getCamera().RenderOffset(m_pTex, &m_irSrc, &m_irDst);
		//TextureManager::Draw(Engine::Instance().GetRenderer(), m_pTex, &m_irSrc, &m_irDst);
	}
}
