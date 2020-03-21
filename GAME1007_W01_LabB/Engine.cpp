#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include "Gun.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include  <SDL.h>
#include <glm\vec2.hpp>
#define GRAV 8.0
#define JUMPFORCE 20.0

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine():g_bRunning(false) , m_bSpaceOk(true)  ,pressSpace(false)                       //class initializer way
{
	time = highScore = 0;
	
}



bool Engine::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (g_pWindow != nullptr) // Window init success.
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr) // Renderer init success.
			{			}
			
			else return false; // Renderer init fail.
			TTF_Init();
			font = TTF_OpenFont("arial.ttf", 25);
			if (Mix_Init(MIX_INIT_MP3) != 0) // MIXER INIT success.
			{
				Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
				m_pMusic = Mix_LoadMUS("../Assets/Audio/music.mp3");
				 m_pPickUps = Mix_LoadWAV("../Assets/Audio/coin.wav");
				 m_pShoot = Mix_LoadWAV("../Assets/Audio/sci-fiShoot.wav");
				 m_pWin = Mix_LoadWAV("../Assets/Audio/win.wav");
				 m_pButtons = Mix_LoadWAV("../Assets/Audio/click.wav");
				 m_pDeath = Mix_LoadWAV("../Assets/Audio/death.wav");;
			}
			else return false;

		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	g_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	g_iKeystates = SDL_GetKeyboardState(nullptr);
	m_src = { 0,0, 800, 400 };
	m_dst = { 0,0, WIDTH, HEIGHT / 2 };
	m_dst2 = { 0,HEIGHT / 2, WIDTH, HEIGHT / 2 };
	m_round = 0;
	m_pCamera = new Camera(Engine::Instance().GetRenderer(), { 0, 0, WIDTH, HEIGHT });
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new TitleState());
	//Mix_PlayMusic(m_pMusic, -1);
	
	g_bRunning = true; // Everything is okay, start the engine.
	
	return true;
}

void Engine::wake()
{
	g_start = SDL_GetTicks();
}

void Engine::sleep()
{
	g_end = SDL_GetTicks();
	g_delta = g_end - g_start;
	if (g_delta < g_fps) // Engine has to sleep.
		SDL_Delay(g_fps - g_delta);
}

void Engine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			g_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_bRunning = false;
		case SDL_KEYUP:
		//	if (event.key.keysym.sym == SDLK_SPACE)
		//		pressSpace = false;
		///*	if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
		//		upButtonad = true;*/
		//	if (event.key.keysym.sym == SDLK_w)
		//		m_bSpaceOk = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button >= 1 && event.button.button <= 3)
			{
				m_MouseState[event.button.button - 1] = true;
				Mix_PlayChannel(-1, m_pButtons, 0);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3)
				m_MouseState[event.button.button - 1] = false;
			break;

		}
	}
}

Engine& Engine::Instance()
{
	static Engine instance;
	return instance;
}


// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (g_iKeystates != nullptr)
	{
		if (g_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::update()
{
	m_pFSM->Update();
}

void Engine::render()
{
	m_pFSM->Render();
}


void Engine::clean()
{
	
	m_pFSM->Clean();
	delete m_pFSM;
	m_pFSM = nullptr;
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

int Engine::run()
{
	if (g_bRunning) // What does this do and what can it prevent?
		return -1;
	if (init("GAME1007_SDL_Setup", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (g_bRunning)
	{
		wake();
		handleEvents();
		update();
		render();
		if (g_bRunning)
			sleep();
	}
	clean();
	return 0;
}

Engine::~Engine()
{
}

TTF_Font* Engine::getFont()
{
	return font;
}

Mix_Chunk* Engine::getShootMixChunk()
{
	return m_pShoot;
}

Mix_Chunk* Engine::getMixChunk()
{
	return m_pPickUps;
}
Mix_Chunk* Engine::getWinMixChunk()
{
	return m_pWin;
}
Mix_Chunk* Engine::getDeathMixChunk()
{
	return m_pDeath;
}
SDL_Renderer* Engine::GetRenderer()
{
	return g_pRenderer;
}

glm::vec2 Engine::getMousePosition()
{
	return m_mousePosition;
}

void Engine::setHighScore(int s)
{
	highScore = s;
}

int Engine::getHighScore()
{
	return highScore;
}

int Engine::getTime()
{
	return time;
}

void Engine::setTime(int t)
{
	time = t;
}

void Engine::QuitGame() { g_bRunning = false; }
bool Engine::GetMouseState(int idx) { return m_MouseState[idx]; }
FSM& Engine::GetFSM()
{
	return *m_pFSM;
}

bool Engine::getSpaceOk()
{
	return m_bSpaceOk;
}

bool Engine::getUpad()
{
	return  upButtonad;
}

bool Engine::getPressSpace()
{
	return pressSpace;
}

void Engine::setPressSpace(bool press)
{
	pressSpace = press;
}

Uint32 Engine::getDelta()
{
	return g_delta;
}

void Engine::setSpaceOk(bool space)
{
	m_bSpaceOk = space;
}

SDL_Rect Engine::getSrcRect()
{
	return m_src;
}

SDL_Rect Engine::getDstRect()
{
	return m_dst;
}

SDL_Rect Engine::getDstRect2()
{
	return m_dst2;
}
