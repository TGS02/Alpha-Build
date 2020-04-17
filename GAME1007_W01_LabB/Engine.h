#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Gun.h"
#include "Map.h"
#include "FSM.h"
#include <glm/vec2.hpp>

class Engine
{
private:   //Properties
	int highScore,time;
	bool g_bRunning; // Loop control flag.
	int g_iSpeed = 5; // Speed of box.
	const Uint8* g_iKeystates; // Keyboard state container.
	Uint32 g_start, g_end, g_delta, g_fps; // Fixed timestep variables.
	SDL_Window* g_pWindow; // This represents the SDL window.
	SDL_Renderer* g_pRenderer; // This represents the buffer to draw to.
	SDL_Texture* m_pTexture;
	SDL_Rect m_src, m_dst, m_dst2;
	int m_round;
	Mix_Music* m_pMusic;
	//Mix_Chunk* m_pPickUps;
	FSM* m_pFSM;
	glm::vec2 m_mousePosition;
	TTF_Font* font;
	bool m_bSpaceOk;
	bool upButtonad;
	SDL_Point m_MousePos;
	int counterSpace;
	bool pressSpace;
	bool m_MouseState[3] = { 0,0,0 };
	Camera* m_pCamera;
	Mix_Chunk* m_pPickUps, * m_pShoot, *m_pWin, *m_pButtons,* m_pDeath;

private:   //methods
	bool init(const char* , int , int , int , int, int);        //you could define all these functions inline(copy the whole function including its body here)
	void wake();
	void sleep();
	void handleEvents();
	Engine();
	void update();
	void render();
	void clean();

public:
	Camera& getCamera() { return *m_pCamera; }
	void setHighScore(int s);
	int getHighScore();
	int getTime();
	void setTime(int t);
	void QuitGame();
	static Engine& Instance();
	bool KeyDown(SDL_Scancode c);
	void renderGameState();
	int run();
	~Engine();
	TTF_Font* getFont();
	Mix_Chunk* getShootMixChunk();
	bool counter = false;
	//getters
	Mix_Chunk* getCoinsChunk();
	Mix_Chunk* getWinMixChunk();
	Mix_Chunk* getDeathMixChunk();
	Mix_Chunk* getMixChunk();
	Mix_Chunk* getButtonChunk();
	SDL_Renderer* GetRenderer();
	glm::vec2 getMousePosition();
	bool GetMouseState(int idx);
	bool getSpaceOk();
	bool getUpad();
	bool getPressSpace();
	void setPressSpace(bool press);
	Uint32 getDelta();
	void setSpaceOk(bool space);
	FSM& GetFSM();
	SDL_Rect getSrcRect();
	SDL_Rect getDstRect();
	SDL_Rect getDstRect2();

};

