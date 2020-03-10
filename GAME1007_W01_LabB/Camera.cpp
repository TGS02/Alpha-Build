#include "Camera.h"
#include "TextureManager.h"

void Camera::UpdatePosition(SDL_Point position)
{
	m_dst.x = position.x - m_dst.w;
	m_dst.y = position.y - m_dst.h;
}

SDL_Rect Camera::Offset(SDL_Rect& dstRect)
{
	SDL_Rect offsetRect = dstRect;
	offsetRect.x -= (m_dst.x + m_dst.w / 2);
	offsetRect.y -= (m_dst.y + m_dst.h / 2);
	return offsetRect;
}

void Camera::RenderOffset(SDL_Renderer* pRenderer, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle, int alpha, SDL_Point* centered, SDL_RendererFlip flip)
{
	TextureManager::draw(pRenderer, tex, src, &Offset(*dst), angle, alpha, centered, flip);
}
