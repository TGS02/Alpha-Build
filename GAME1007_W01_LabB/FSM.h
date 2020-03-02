
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Timer.h"
#include "Gun.h"
#include "Button.h"
#include "Map.h"
#include "Player.h"
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
	Mix_Music* m_pMusic;
	SDL_Texture* m_pTexture;
	SDL_Rect src, dst;
	vector<Button*> m_vButtons;
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();


};
class EndState : public State
{
private:
	Mix_Music* m_pMusic;
	SDL_Texture* m_pTexture;
	SDL_Rect src, dst;
	vector<Button*> m_vButtons;
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
public:
	EndState();
	void Enter();
	void Update();
	void Render();
	void Exit();


};
class GameState : public State
{
public:
	Mix_Music* m_pMusic;
	GameState();
	~GameState();
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume();
	bool GetShoot();
	void setShoot(bool tmpshoot);
	bool p_score = false;
	int p_record = 0;
	bool p_finish = false;
	bool shoot;
private:
	int jumpTime;
	int record,score;
	SDL_Surface* surface;
	SDL_Texture* texture, *m_pScoreTexture,*m_pTexture, *barTexture;
	SDL_Rect bar_src, bar_dst;;
	SDL_Rect src, dst, score_src, score_dst;
	int counterSpace;
	TTF_Font* font;
	Map* map; // handle pointers properly.
	Player* m_pPlayer;
	Gun* gun;
	SDL_Texture* bgTexture; //engine 
	int countFinish;
	bool drawBackground;
};


class TitleState : public State
{
private:
	Mix_Music* m_pMusic;
	SDL_Texture* m_pBGText;
	SDL_Rect m_src, m_dst;
	vector<Button*> m_vButtons;
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

