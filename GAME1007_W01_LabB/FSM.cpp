#include "FSM.h"
#include "Engine.h"
#include "Gamedata.h"
#include <iostream>
#include <sstream>
using namespace std;

//FSM. Begins
FSM::FSM() {}
FSM::~FSM() {}

void FSM::Update()
{
	if (!m_vStates.empty())
		m_vStates.back()->Update();
}

void FSM::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render();
}

void FSM::ChangeState(State* state)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();

	}
	PushState(state);
}

void FSM::PushState(State* pstate)
{
	pstate->Enter();
	m_vStates.push_back(pstate);
}

void FSM::PopState()
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::Clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::GetState()
{
	return m_vStates;
}

//FSM. Ends

// State Begins
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume() {}

// State Ends

//Pause State Begins
PauseState::PauseState()
{
	m_pTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/PauseState.png");
	src = { 0, 0, 1024, 768 };
	dst = { 0 , 0, 1024, 768 };
}

void PauseState::Enter()
{
	cout << "Entering Pause state....." << endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		Engine::Instance().GetFSM().PopState();
}

void PauseState::Render()
{
	//cout << "Rendering Pause state....." << endl;
	Engine::Instance().GetFSM().GetState().front()->Render();
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, &src, &dst);
	State::Render();

}

void PauseState::Exit()
{
	cout << "Exiting Pause state....." << endl;
}
//Pause State Ends

//Game State Begins
GameState::GameState() {}

GameState::~GameState()
{
	SDL_DestroyTexture(texture);


}

void GameState::Enter()
{
	cout << "Entering Game state....." << endl;
	GameData::Instance()->getLevelSet(0)->getDatum(0)->LoadFromXML();
	m_pPlayer = new Player();
	m_pPlayer->loadPlayer(Engine::Instance().GetRenderer());
	m_pGun = new Gun(glm::vec2(m_pPlayer->getPosition().x + (m_pPlayer->getSize().x / 2), m_pPlayer->getPosition().y + (m_pPlayer->getSize().y / 2)));
	m_pGun->loadGun(Engine::Instance().GetRenderer());
	myTimer.start();
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		Engine::Instance().GetFSM().PushState(new PauseState());
		cout << "P pressed" << endl;
		myTimer.pause();
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		Engine::Instance().GetFSM().ChangeState(new TitleState());
		myTimer.stop();
	}
	m_pPlayer->playerUpdate();
	if (Engine::Instance().getMousePosition().x < m_pPlayer->getPosition().x) {
		m_pPlayer->setRotation(true);
		m_pGun->setRotation(true);
	}
	if (Engine::Instance().getMousePosition().x > m_pPlayer->getPosition().x) {
		m_pPlayer->setRotation(false);
		m_pGun->setRotation(false);
	}
	m_pGun->setPosition(glm::vec2(m_pPlayer->getPosition().x + (m_pPlayer->getSize().x / 2), m_pPlayer->getPosition().y + (m_pPlayer->getSize().y / 2)));
	m_pGun->setMousePosition(Engine::Instance().getMousePosition());
	m_pGun->update();
}

void GameState::Render()
{
	//cout << "Rendering Game state....." << endl;
	//cout << myTimer.get_ticks() / 1000.f << endl;
	Engine::Instance().renderGameState();

	if (Engine::Instance().getFont() == nullptr)
		cout << TTF_GetError();
	std::stringstream timeText;
	timeText.str("");
	timeText << "Time:  " << myTimer.get_ticks() / 1000;
	SDL_Color color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(Engine::Instance().getFont(), timeText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_FreeSurface(surface);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	// Render the player
	m_pPlayer->playerDraw(Engine::Instance().GetRenderer());
	m_pGun->draw(Engine::Instance().GetRenderer());

	if (dynamic_cast<GameState*> (Engine::Instance().GetFSM().GetState().back()))
	{
		State::Render();
	}


}

void GameState::Exit()
{
	cout << "Exiting Game state....." << endl;
	m_pGun->clean();
	delete m_pGun;
	m_pGun = nullptr;
	m_pPlayer->clean();
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void GameState::Resume()
{
	cout << "Resuming Game state....." << endl;
	myTimer.unpause();
}

// Game State Ends

// Title State Begins
TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering Title state....." << endl;
	GameData::Instance()->LoadFromXML();
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
		Engine::Instance().GetFSM().ChangeState(new GameState());
}

void TitleState::Render()
{
	//cout << "Rendering Title state....." << endl;
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_Texture* m_pTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/TitleState.png");
	SDL_Rect src = { 0, 0, 1024, 768 };
	SDL_Rect dst = { 0 , 0, 1024, 768 };
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, &src, &dst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting Title state....." << endl;
}

// Title State Ends