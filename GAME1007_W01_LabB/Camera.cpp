#include "Camera.h"
#include "TextureManager.h"

void Camera::UpdatePosition(SDL_Point position)
{
	m_dst.x = position.x - m_dst.w + m_dst.w / 2;
	m_dst.y = position.y - m_dst.h + m_dst.h / 2;
}

SDL_Rect Camera::Offset(SDL_Rect& dstRect)
{
	SDL_Rect offsetRect = dstRect;
	offsetRect.x -= m_dst.x;
	offsetRect.y -= m_dst.y;
	return offsetRect;
}

void Camera::RenderOffsetEx(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle, int alpha, SDL_Point* centered, SDL_RendererFlip flip)
{
	TextureManager::draw(m_pRenderer, tex, src, &Offset(*dst), angle, alpha, centered, flip);
}

void Camera::RenderOffset(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst)
{
	TextureManager::Draw(m_pRenderer, tex, src, &Offset(*dst));
}
