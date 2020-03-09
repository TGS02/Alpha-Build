#include <iostream>
#include "Button.h"
#include "Engine.h"
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

Button::Button(const char* s, SDL_Rect src, SDL_Rect dst, std::function<void()> cb)
	: m_rSrc(src), m_rDst(dst), m_iFrame(0)
{
	cout << "Constructing button!" << endl;
	// Set the button image. You should have some fail checking just in case. 
	m_pText = IMG_LoadTexture(Engine::Instance().GetRenderer(), s);
	// Setting the callback.
	m_callback = cb;
}

Button::~Button()
{
	SDL_DestroyTexture(m_pText);
}

bool Button::MouseCollision()
{
	int mx = Engine::Instance().getMousePosition().x;
	int my = Engine::Instance().getMousePosition().y;
	return (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x &&
		my < (m_rDst.y + m_rDst.h) && my > m_rDst.y);
}

void Button::Update()
{
	bool col = MouseCollision();
	bool willCallback = false;
	switch (m_iFrame)
	{
	case MOUSE_UP:
		if (col)
			m_iFrame = MOUSE_OVER;
		break;
	case MOUSE_OVER:

		if (!col)
			m_iFrame = MOUSE_UP;
		else if (col && Engine::Instance().GetMouseState(0))
			m_iFrame = MOUSE_DOWN;
		break;
	case MOUSE_DOWN:
		if (!Engine::Instance().GetMouseState(0))
		{
			if (col)
			{
				m_iFrame = MOUSE_OVER;
				// Execute callback.
				willCallback = true;
			}
			else
				m_iFrame = MOUSE_UP;
		}
		break;
	}
	if (willCallback)
		m_callback();
}

void Button::Render()
{
	m_rSrc.x = m_rSrc.w * m_iFrame;
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pText, &m_rSrc, &m_rDst);
}