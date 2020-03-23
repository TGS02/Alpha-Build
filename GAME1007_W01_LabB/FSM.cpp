#include "FSM.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#include "GameData.h"
#include "Weapon.h"
using namespace std;
#define GRAV 8.0
#define JUMPFORCE 20.0

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
	Clean();
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
	m_pTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Board.png");
	src = { 0, 0, 512, 512 };
	dst = { 256 , 128, 512, 512 };
}

void PauseState::Enter()
{
	
	cout << "Entering Pause state....." << endl;
	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 360,250,300,80 },
		std::bind(&FSM::PopState, &Engine::Instance().GetFSM())));
	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 360,350,300,80 },
		std::bind(&Engine::QuitGame, &Engine::Instance())));
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		Engine::Instance().GetFSM().PopState();
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void PauseState::Render()
{
	//cout << "Rendering Pause state....." << endl;
	Engine::Instance().GetFSM().GetState().front()->Render();
	
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, &src, &dst);
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();

}

void PauseState::Exit(){ }
//Pause State Ends

//Game State Begins
GameState::GameState(int i)
{
	activeLevelSet = 0;
	activeLevel = i;
	GameData::Instance()->getLevelSet(activeLevelSet)->getDatum(activeLevel)->LoadFromXML();
	m_pTileMap = GameData::Instance()->getLevelSet(activeLevelSet)->getDatum(activeLevel)->getTileMap();
	drawBackground = true;
	jumpTime = 0;
	counterSpace = 0;
	record = 0;
	score = 0;
	shoot = false;
	//bgTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/test.png");
	//map = new Map(Engine::Instance().GetRenderer());
	m_pPlayer = new Player();
	m_pPlayer->loadPlayer(Engine::Instance().GetRenderer());
	m_pPlayer->setWeapon(GameData::Instance()->getWeaponSet(0)->getDatum(0));
	m_pPlayer->setTileMap(m_pTileMap);
	gun = new Gun(glm::vec2(m_pPlayer->getPosition().x + (m_pPlayer->getSize().x / 2), m_pPlayer->getPosition().y + (m_pPlayer->getSize().y / 2)));
	gun->loadGun(Engine::Instance().GetRenderer());
	countFinish = 0;
	m_pTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/time.png");
	m_pScoreTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/score.png");
	BG_text = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Space_Background.png");
	crosshair_text = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Crosshair.png");
	cross_src = { 0,0,32,32 };

	cross_dst = { 0,0, cross_src.w,cross_src.h };
	bg_src = { 0,0,1024,768 };
	bg_dst = { 0,0,bg_src.w,bg_src.h };
	score_src = src = { 0,0,970,80 };
	dst = { 0,-8,970,80 };
	score_dst = { 925 , -8, 970, 80 };
}

GameState::~GameState()
{
	SDL_DestroyTexture(texture);
	//SDL_DestroyTexture(bgTexture);

	gun->clean();
	delete gun;
	gun = nullptr;

	//map->clean();
	//delete map;
	//map = nullptr;

	m_pPlayer->clean();
	delete m_pPlayer;
	m_pPlayer = nullptr;

}

void GameState::Enter()
{
	SDL_ShowCursor(SDL_DISABLE);
	Engine::Instance().getCamera().SetBounds(m_pTileMap->getBounds());
	m_pMusic = Mix_LoadMUS("../Assets/Audio/Music.mp3");
	myTimer.start();
	Mix_PlayMusic(m_pMusic, -1);
	barTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/bar.png");
	bar_src = {0 ,0 , 170, 60};
	bar_dst = {5 , 700, 170,60 };
	m_pPlayer->setStartingTile(m_pTileMap->findStartingTile());
	m_pPlayer->setPosition(m_pPlayer->getStartingPosition());
}

void GameState::Update()
{
	mouseposx = Engine::Instance().getMousePosition().x;
	mouseposy = Engine::Instance().getMousePosition().y;
	cross_dst.x = mouseposx - (cross_src.w /2);
	cross_dst.y = mouseposy - (cross_src.h /2);

	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		m_pPlayer->reload();
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->getAcceleration().x -= m_pPlayer->getControl();
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->getAcceleration().x += m_pPlayer->getControl();
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W) || Engine::Instance().KeyDown(SDL_SCANCODE_SPACE))
	{
		m_pPlayer->jump(true);
	}
	else
	{
		m_pPlayer->jump(false);
	}
	if (Engine::Instance().GetMouseState(0))
	{
		m_pPlayer->shoot({ gun->getCurrentDirection().x, gun->getCurrentDirection().y });
	}

	//if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
	//{
	//	m_pPlayer->jump();
	//	//if (m_pPlayer->IsGrounded() == true) {
	//		//Engine::Instance().setSpaceOk( false); // This just prevents repeated jumps when holding spacebar.
	//		//m_pPlayer->SetAccelY(-JUMPFORCE); // Sets the jump force.
	//		//m_pPlayer->SetGrounded(false);
	//	//}
	//}
	//if(Engine::Instance().KeyDown(SDL_SCANCODE_SPACE))
	//{
	//	m_pPlayer->jump();
	//	//Engine::Instance().setPressSpace(true);
	//	//counterSpace++;
	//}
	//if (!Engine::Instance().getPressSpace() && counterSpace!=0)
	//{
	//	Mix_PlayChannel(-1, Engine::Instance().getShootMixChunk(), 0);
	//	gun->getShootFsm(true);
	//	//if (counterSpace >= 1 && counterSpace <= 10) {
	//		m_pPlayer->SetVelX(-gun->getCurrentDirection().x * 20);
	//		m_pPlayer->SetVelY(-gun->getCurrentDirection().y * 20);
	//	//}
	/*	if (counterSpace >= 11 && counterSpace <= 25) {

			m_pPlayer->SetVelX(-gun->getCurrentDirection().x * 30);
			m_pPlayer->SetVelY(-gun->getCurrentDirection().y * 30);
		}
		if (counterSpace >= 25 ) {

			m_pPlayer->SetVelX(-gun->getCurrentDirection().x * 40);
			m_pPlayer->SetVelY(-gun->getCurrentDirection().y * 40);
		}*/

	//	counterSpace = 0;
	//}



	m_pPlayer->playerUpdate();
	//m_pPlayer->SetAccelY(0.0); // After jump, reset vertical acceleration.

	if (Engine::Instance().getMousePosition().x < m_pPlayer->getPosition().x) {
		m_pPlayer->setRotation(true);
		gun->setRotation(true);
	}
	if (Engine::Instance().getMousePosition().x > m_pPlayer->getPosition().x) {
		m_pPlayer->setRotation(false);
		gun->setRotation(false);
	}
	gun->setPosition(glm::vec2(m_pPlayer->getPosition().x + (m_pPlayer->getSize().x / 3 + 6), m_pPlayer->getPosition().y + (m_pPlayer->getSize().y / 3 + 3)));
	gun->setMousePosition(Engine::Instance().getMousePosition());
	gun->update();
	m_pTileMap->update();

	if (m_pPlayer->getDie())
	{
		gun->getPlayerDie(true);
	}
	
	if (m_pPlayer->finish==true)
	{
		
		//map->getFinishFsm(true);
		countFinish++;
		if(countFinish==10)
		m_pPlayer->stop = true;
		if (countFinish == 27) {
			Engine::Instance().GetFSM().ChangeState(new EndState());
			myTimer.stop();
			countFinish = 0;
		}
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	     {
		Engine::Instance().GetFSM().PushState(new PauseState());
		
		myTimer.pause();
	     }
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		Engine::Instance().GetFSM().ChangeState(new TitleState());
		myTimer.stop();
	}
}
bool GameState::GetShoot()
{
	return shoot;
}

void GameState::setShoot(bool tmpshoot)
{
	shoot = tmpshoot;
}

void GameState::Render()
{
	//cout << "Rendering Game state....." << endl;

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_RenderCopy(Engine::Instance().GetRenderer(), BG_text, &bg_src, &bg_dst);

	GameData::Instance()->getLevelSet(activeLevelSet)->getDatum(activeLevel)->getTileMap()->draw();
	
	// Render the player
	if (gun->left == false) {
		m_pPlayer->SetLeft(false);
		m_pPlayer->playerDraw(Engine::Instance().GetRenderer());
		
	}
	else {
		m_pPlayer->SetLeft(true);
		m_pPlayer->playerDraw(Engine::Instance().GetRenderer());

	}
	gun->draw(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), crosshair_text, &cross_src, &cross_dst);
	
	/*if (Engine::Instance().getFont() == nullptr)
		cout << TTF_GetError();*/
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture, &src, &dst);
	std::stringstream timeText, scoreText, lastRec;
	timeText.str("");
	timeText << myTimer.get_ticks() / 1000;
	if(!m_pPlayer->finish)
	Engine::Instance().setTime(myTimer.get_ticks() / 1000);
	
	SDL_Color color = { 0, 0, 0 };
	surface = TTF_RenderText_Solid(Engine::Instance().getFont(), timeText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 60, 0, texW, texH };
	SDL_FreeSurface(surface);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	score += m_pPlayer->record;
	Engine::Instance().setHighScore(m_pPlayer->record);

	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pScoreTexture, &score_src, &score_dst);
	scoreText << m_pPlayer->record;
	surface = TTF_RenderText_Solid(Engine::Instance().getFont(), scoreText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 990, 0, texW, texH };
	SDL_FreeSurface(surface);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), barTexture, &bar_src, &bar_dst);
	if (m_pPlayer->finish == true)
	{

		record = myTimer.get_ticks() / 1000;
		lastRec << "Last Record:  " << record - (score % 10);

		myTimer.start();
	}
	if (dynamic_cast<GameState*> (Engine::Instance().GetFSM().GetState().back()))
	{
		State::Render();
	}
}

void GameState::Exit()
{
	cout << "Exiting Game state....." << endl;
	SDL_ShowCursor(SDL_ENABLE);
	Mix_FreeMusic(m_pMusic);
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
	GameData::Instance()->LoadFromXML();
	m_pMusic = Mix_LoadMUS("../Assets/Audio/Music.mp3");
	cout << "Entering Title state....." << endl;
	m_pBGTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_bgSrc = { 0, 0, 1024, 768 };
	m_bgDst = { 0 , 0, 1024, 768 };
	
	m_pLogoTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/(Cowboy) Cadet.png");
	m_logoSrc = { 0, 0, 836, 420 };
	m_logoDst = { (1024 / 2) - (836 / 4), 100, 836 / 2, 420 / 2 };

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 360,350,300,80 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState(0))));

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 360,450,300,80 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new LevelSelect())));

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 360,550,300,80 },
		std::bind(&Engine::QuitGame, &Engine::Instance())));
	Mix_PlayMusic(m_pMusic, -1);
}

void TitleState::Update()
{
	
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void TitleState::Render()
{
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTex, &m_bgSrc, &m_bgDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pLogoTex, &m_logoSrc, &m_logoDst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting Title state....." << endl;
	Mix_FreeMusic(m_pMusic);
}

// Title State Ends

EndState::EndState()
{
	
}

void EndState::Enter()
{
	m_pMusic = Mix_LoadMUS("../Assets/Audio/Music.mp3");
	font = TTF_OpenFont("arial.ttf", 40);
	Mix_PlayMusic(m_pMusic, -1);
	
	cout << "Entering End state....." << endl;
	m_pTexture[0] = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_pTexture[1] = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Board.png");
	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 315,450,100,50 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new TitleState())));
	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 615,450,100,50 },
		std::bind(&Engine::QuitGame, &Engine::Instance())));
}



void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		Engine::Instance().GetFSM().ChangeState(new TitleState());
		/*Engine::Instance().getPlayer()->finish = false;*/
		// Mary - dil wit it.
	}
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void EndState::Render()
{
	
	SDL_Rect src = { 0, 0, 1024, 768 };
	SDL_Rect dst = { 0 , 0, 1024, 768 };
	SDL_Rect boardsrc = { 0,0,512,512 };
	SDL_Rect boarddst = { 256,128,512,512 };
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[0], &src, &dst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[1], &boardsrc, &boarddst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	std::stringstream scoreText;
	scoreText.str("");
	scoreText << "" << Engine::Instance().getHighScore();
	SDL_Color color = { 0, 0, 0 };
	surface = TTF_RenderText_Solid(font, scoreText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 352, 300, texW, texH };
	SDL_FreeSurface(surface);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);


	std::stringstream timeText;
	timeText.str("");
	timeText << "" << Engine::Instance().getTime();;
	color = { 0, 0, 0 };
	surface = TTF_RenderText_Solid(font, timeText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 652, 300, texW, texH };
	SDL_FreeSurface(surface);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting End state....." << endl;
	Mix_FreeMusic(m_pMusic);
}

LevelSelect::LevelSelect()
{
}

void LevelSelect::Enter()
{
	GameData::Instance()->LoadFromXML();
	m_pMusic = Mix_LoadMUS("../Assets/Audio/Music.mp3");
	cout << "Entering Title state....." << endl;
	m_pBGTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_bgSrc = { 0, 0, 1024, 768 };
	m_bgDst = { 0 , 0, 1024, 768 };

	m_pLogoTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Board.png");
	m_logoSrc = { 0, 0, 512, 512 };
	m_logoDst = { 128,64,768,634 };

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 200,350,250,60 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState(0))));

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 600,350,250,60 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState(1))));

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 200,600,250,60 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState(2))));

	m_vButtons.push_back(new Button("../Assets/Textures/Button.png", { 0,0,600,156 }, { 600,600,250,60 },
		std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState(0))));
	
	Mix_PlayMusic(m_pMusic, -1);
}

void LevelSelect::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void LevelSelect::Render()
{
	
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTex, &m_bgSrc, &m_bgDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pLogoTex, &m_logoSrc, &m_logoDst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 220, 125, 200, 200 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);

	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void LevelSelect::Exit()
{
}
