#pragma once
#include <functional>
#include "SDL.h"

class Button
{
private:
	enum state { MOUSE_UP, MOUSE_OVER, MOUSE_DOWN };
	int m_iFrame;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;
	bool rendflip;
	std::function<void()> m_callback; // The button callback!
	virtual void Execute() = 0;
public:
	Button(const char* s, SDL_Rect src, SDL_Rect dst, bool flip);
	~Button();
	bool MouseCollision();
	void Update();
	void Render();
};

class PlayButton : public Button
{
private:
	void Execute();
public:
	PlayButton(const char* s, SDL_Rect src, SDL_Rect dst, int levelset, int level, bool flip);
	int plevelset;
	int plevel;
};

class ExitButton : public Button
{
private:
	void Execute();
public:
	ExitButton(const char* s, SDL_Rect src, SDL_Rect dst,bool flip);
};

class ResumeButton : public Button
{
private:
	void Execute();
public:
	ResumeButton(const char* s, SDL_Rect src, SDL_Rect dst,bool flip);
};

class MainMenuButton : public Button
{
private:
	void Execute();
public:
	MainMenuButton(const char* s, SDL_Rect src, SDL_Rect dst, bool flip);
};

class LevelSelectButton : public Button
{
private:
	void Execute();
public:
	int plevelset;
	LevelSelectButton(const char* s, SDL_Rect src, SDL_Rect dst, int levelset, bool flip);
};