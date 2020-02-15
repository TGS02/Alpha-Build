#pragma once
#include "Engine.h"
class TextureManager
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* m_pRenderer,const char* fileName);
	static void Draw(SDL_Renderer* m_pRenderer,SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst);
	static void DrawLeft(SDL_Renderer* m_pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst);
	static void draw(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle, int alpha, SDL_Point* centered, SDL_RendererFlip flip);
};

