#pragma once
#include <SDL.h>
#include <glm\vec2.hpp>
#include <iostream>

class Camera
{
private:
	SDL_Rect m_dst;
	SDL_Rect m_WorldBounds; // Is it necessary to have this here? Would it be possible to load this or calculate it directly from the tileMap or GameState? Would doing so be preferable?
	SDL_Renderer* m_pRenderer; // This is here for the benefit of not having to access it from the engine every call - fewer function calls all aronud.
public:
	Camera(SDL_Renderer* renderer, SDL_Rect screen = { 0, 0, 1024, 768 }) : m_pRenderer(renderer), m_dst(screen) {}
	SDL_Rect& getDst() { return m_dst; }
	void SetBounds(SDL_Rect bounds) { m_WorldBounds = bounds; } // Likewise as above^^
	void UpdatePosition(SDL_Point position);
	SDL_Rect Offset(SDL_Rect& dstRect);
	void RenderOffsetEx(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle = 0.0, int alpha = 0, SDL_Point* centered = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void RenderOffset(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst);
};
