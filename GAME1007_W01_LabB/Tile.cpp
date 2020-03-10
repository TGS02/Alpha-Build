#include "Tile.h"
#include "Engine.h"
#include "TextureManager.h"

void Tile::draw()
{
	Engine::Instance().getCamera().RenderOffset(Engine::Instance().GetRenderer(), m_pTex, &m_irSrc, &m_irDst);
	//TextureManager::Draw(Engine::Instance().GetRenderer(), m_pTex, &m_irSrc, &m_irDst);
}
