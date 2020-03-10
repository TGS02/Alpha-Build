#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* m_pRenderer, const char* fileName)
{
	SDL_Texture* tex = IMG_LoadTexture(m_pRenderer, fileName);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	return tex;
}

void TextureManager::Draw(SDL_Renderer* m_pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst)
{
	SDL_RenderCopy(m_pRenderer, tex, src, dst);

}

void TextureManager::DrawLeft(SDL_Renderer* m_pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst)
{
	
	SDL_RenderCopyEx(m_pRenderer, tex, src, dst, NULL, NULL,	SDL_FLIP_HORIZONTAL);
}

void TextureManager::draw(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle,
	int alpha, SDL_Point* centered, SDL_RendererFlip flip)
{

	SDL_RenderCopyEx(pRenderer, tex, src, dst, angle,centered , flip);

}
