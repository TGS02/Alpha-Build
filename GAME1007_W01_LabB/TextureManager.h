#pragma once
#include "Engine.h"
class TextureManager
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* m_pRenderer,const char* fileName);
	static void Draw(SDL_Renderer* m_pRenderer,SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst);
	static void DrawLeft(SDL_Renderer* m_pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst);
	static void draw(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle = 0.0, int alpha = 0, SDL_Point* centered = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

