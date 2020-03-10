#pragma once
#include <SDL.h>
#include <glm\vec2.hpp>
#include <iostream>

class Camera
{
private:
	SDL_Rect m_dst;
	SDL_Rect m_WorldBounds; // Is it necessary to have this here? Would it be possible to load this or calculate it directly from the tileMap or GameState? Would doing so be preferable?
public:
	Camera() : m_dst({ 0, 0, 1024, 768 }) {}
	//void UpdatePosition(glm::vec2 pos) { m_dst.x = pos.x - m_dst.w; m_dst.y = pos.y - m_dst.h; }
	void UpdatePosition(SDL_Point position);
	SDL_Rect Offset(SDL_Rect& dstRect);
	void RenderOffset(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle = 0.0, int alpha = 0, SDL_Point* centered = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};