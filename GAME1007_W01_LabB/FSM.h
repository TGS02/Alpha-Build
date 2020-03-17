
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Timer.h"
#include "Gun.h"
#include "Button.h"
#include "Map.h"
#include "Player.h"
#include "Scorecard.h"
#include "TileMap.h"
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
	Scorecard* m_pScorecard;
	Mix_Music* m_pMusic;
	SDL_Texture* m_pTexture[2];
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
	void setScorecard(Scorecard* scorecard) { m_pScorecard = scorecard; }


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
	Player* getPlayer() { return m_pPlayer; }
	bool GetShoot();
	void setShoot(bool tmpshoot);
	Scorecard* getScorecard() { return m_pScorecard; }
	TileMap* getTileMap() { return m_pTileMap; }
	bool p_score = false;
	int p_record = 0;
	bool p_finish = false;
	bool shoot;
	unsigned int activeLevel = 0;
	unsigned int activeLevelSet = 0;
	int mouseposx, mouseposy;
private:
	TileMap* m_pTileMap;
	Scorecard* m_pScorecard;
	int jumpTime;
	int record,score;
	SDL_Surface* surface;
	SDL_Texture* texture, *m_pScoreTexture,*m_pTexture, *barTexture, *BG_text, * crosshair_text;
	SDL_Rect bar_src, bar_dst, bg_src, cross_src, cross_dst;
	SDL_Rect src, dst, score_src, score_dst,bg_dst;
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
	SDL_Texture* m_pBGTex;
	SDL_Texture* m_pLogoTex;
	SDL_Rect m_bgSrc, m_bgDst, m_logoSrc, m_logoDst;
	vector<Button*> m_vButtons;
public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class LevelSelect : public State
{
private:
	Mix_Music* m_pMusic;
	SDL_Texture* m_pBGTex;
	SDL_Texture* m_pLogoTex;
	SDL_Rect m_bgSrc, m_bgDst, m_logoSrc, m_logoDst;
	vector<Button*> m_vButtons;
public:
	LevelSelect();
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

