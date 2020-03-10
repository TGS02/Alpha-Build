#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* m_pRenderer, const char* fileName)
{
	return IMG_LoadTexture(m_pRenderer, fileName);
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
	if (centered != nullptr)
	{
		SDL_RenderCopyEx(pRenderer, tex, src, dst, angle, centered , flip);
	}
	else
	{
		SDL_Point pivot = { dst->x + dst->w / 2, dst->y + dst->h / 2 };
		SDL_RenderCopyEx(pRenderer, tex, src, dst, angle, &pivot, flip);
	}
}
