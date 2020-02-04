#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include "Gun.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include  <SDL.h>
#include <glm\vec2.hpp>

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine():g_bRunning(false)                          //class initializer way
{
	cout << "Constructing engine class...\n";
	
}



bool Engine::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (g_pWindow != nullptr) // Window init success.
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr) // Renderer init success.
			{
				m_pTexture = IMG_LoadTexture(g_pRenderer, "../Assets/Textures/Background_1.png");
				map = new Map(g_pRenderer);
				player = new Player();
				player->loadPlayer(g_pRenderer);
			
				gun = new Gun(glm::vec2(player->getPosition().x + (player->getSize().x / 2), player->getPosition().y + (player->getSize().y / 2)));
				gun->loadGun(g_pRenderer);
			}
			
			else return false; // Renderer init fail.
			TTF_Init();
			font = TTF_OpenFont("arial.ttf", 25);
			if (Mix_Init(MIX_INIT_MP3) != 0) // MIXER INIT success.
			{
				Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
				m_pMusic = Mix_LoadMUS("../Assets/Audio/bgMusic.mp3");
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
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new TitleState());
	Mix_PlayMusic(m_pMusic, -1);
	g_bRunning = true; // Everything is okay, start the engine.
	cout << "Success!" << endl;
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
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_bRunning = false;
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
	player->playerUpdate(map);
	if (m_mousePosition.x < player->getPosition().x) {
		player->setRotation(true);
		gun->setRotation(true);
	}
	if (m_mousePosition.x > player->getPosition().x) {
		player->setRotation(false);
		gun->setRotation(false);
	}
	gun->setPosition(glm::vec2(player->getPosition().x + (player->getSize().x / 2), player->getPosition().y + (player->getSize().y / 2)));
	gun->setMousePosition(Engine::getMousePosition());
	gun->update();
}

void Engine::render()
{
	m_pFSM->Render();
	
	
}

void Engine::renderGameState()
{
	
		SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(g_pRenderer); // Clear the screen with the draw color.

		// Render the overall background
		//SDL_RenderCopy(g_pRenderer, m_pTexture, &m_src, &m_dst);
		//SDL_RenderCopy(g_pRenderer, m_pTexture, &m_src, &m_dst2);

		// Render the tiling background
		vector<int> num = { 1 };
		map->DrawBG(g_pRenderer, num);
		num.clear();

		// Render the tiles with z < the player
		num = { 1,2,3,5,12,13,14,15,16,31,32,33,34,41,42 };
		map->DrawMap(g_pRenderer, num);
		num.clear();

		// Render the player
		player->playerDraw(g_pRenderer);
		gun->draw(g_pRenderer);
		// Render tiles with z > the player
		num = { 21,22 };
		map->DrawMap(g_pRenderer, num);
		num.clear();

		// Draw anew.
	
}

void Engine::clean()
{
	cout << "Cleaning game." << endl;
	gun->clean();
	delete gun;
	gun = nullptr;
	m_pFSM->Clean();
	delete m_pFSM;
	m_pFSM = nullptr;
	map->clean();
	delete map;
	map = nullptr;
	player->clean();
	delete player;
	player = nullptr;

	SDL_DestroyTexture(m_pTexture);
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

SDL_Renderer* Engine::GetRenderer()
{
	return g_pRenderer;
}

glm::vec2 Engine::getMousePosition()
{
	return m_mousePosition;
}

FSM& Engine::GetFSM()
{
	return *m_pFSM;
}
