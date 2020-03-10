#include "Camera.h"
#include "TextureManager.h"

SDL_Rect Camera::Offset(SDL_Rect& dstRect)
{
	SDL_Rect offsetRect = dstRect;
	// modify the position of offsetRect
	return offsetRect;
}

void Camera::RenderOffset(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle, int alpha, SDL_Point* centered, SDL_RendererFlip flip)
{
	SDL_Rect offsetRect = *dst;
	offsetRect.x += 8;
	offsetRect.y += 8;
	// Do stuff to offsetRect
	TextureManager::draw(pRenderer, tex, src, &offsetRect, angle, alpha, centered, flip);
}
