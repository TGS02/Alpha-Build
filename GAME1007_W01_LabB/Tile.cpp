#include "Tile.h"
#include "Engine.h"
#include "TextureManager.h"

void Tile::draw()
{
	TextureManager::Draw(Engine::Instance().GetRenderer(), m_pTex, &m_irSrc, &m_irDst);
}
