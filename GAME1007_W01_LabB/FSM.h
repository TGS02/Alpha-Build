
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Timer.h"
using namespace std;

class State
{
protected:
	State() {}
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
	Timer myTimer;
};

class PauseState : public State
{
private:
	SDL_Texture* m_pTexture;
	SDL_Rect src, dst;
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();


};
class GameState : public State
{
public:
	GameState();
	~GameState();
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume();
private:

	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;

};
class TitleState : public State
{
private:
public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};
class FSM
{
private:
	vector<State*> m_vStates;
public:
	FSM();
	~FSM();
	void Update();
	void Render();
	void ChangeState(State* pstate);
	void PushState(State* pstate);
	void PopState();
	void Clean();
	vector<State*>& GetState();
};

