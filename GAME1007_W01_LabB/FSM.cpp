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
	m_vButtons.push_back(new ResumeButton("../Assets/Textures/Buttons/Button_Resume.png", { 0,0,600,156 }, { 360,250,300,80 }, false));
	m_vButtons.push_back(new MainMenuButton("../Assets/Textures/Buttons/Button_Mainmenu.png", { 0,0,600,156 }, { 360,350,300,80 },false));
	m_vButtons.push_back(new ExitButton("../Assets/Textures/Buttons/Button_Quit.png", { 0,0,600,156 }, { 360,450,300,80 },false));
	SDL_ShowCursor(SDL_ENABLE);
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
GameState::GameState(int j, int i)
{
	activeLevelSet = i;
	activeLevel = j;
	GameData::Instance()->getLevelSet(activeLevelSet)->getDatum(activeLevel)->LoadFromXML();
	m_pTileMap = GameData::Instance()->getLevelSet(activeLevelSet)->getDatum(activeLevel)->getTileMap();
	drawBackground = true;
	jumpTime = 0;
	counterSpace = 0;
	record = 0;
	score = 0;
	m_pScorecard = new Scorecard(0, 0, 0, 0, 0, 0);
	shoot = false;
	//bgTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/test.png");
	//map = new Map(Engine::Instance().GetRenderer());
	m_pPlayer = new Player();
	m_pPlayer->loadPlayer(Engine::Instance().GetRenderer());
	m_pPlayer->setWeapon(GameData::Instance()->getWeaponSet(0)->getDatum(0));
	m_pPlayer->setTileMap(m_pTileMap);
	m_pPlayer->loadAmmoUI(Engine::Instance().GetRenderer());
	gun = new Gun(glm::vec2(m_pPlayer->getPosition().x + (m_pPlayer->getSize().x / 2), m_pPlayer->getPosition().y + (m_pPlayer->getSize().y / 2)));
	gun->loadGun(Engine::Instance().GetRenderer());
	countFinish = 0;
	m_pTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/time.png");
	m_pScoreTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/score.png");
	BG_text = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Space_Background.png");
	crosshair_text = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Crosshair.png");
	controls_text = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Controls.png");
	control_src = { 0,0,110,125 };
	control_dst = { 20,50,110,125 };
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
	m_pMusic = Mix_LoadMUS("../Assets/Audio/the_cowboys_curse.wav");
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
	if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE))
	{
		//m_pPlayer->m_inAirTimer.start();
		m_pPlayer->jump(true);
		Engine::Instance().counter = true;
	}
	else
	{
		m_pPlayer->jump(false);
	}
	if (Engine::Instance().GetMouseState(0))
	{
		//m_pPlayer->m_inAirTimer.start();
		m_pPlayer->shoot({ gun->getCurrentDirection().x, gun->getCurrentDirection().y });
		Engine::Instance().counter = true;
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
		Mix_PlayChannel(-1, Engine::Instance().getWinMixChunk(), 0);
		//map->getFinishFsm(true);
		countFinish++;
		if(countFinish==10)
		m_pPlayer->stop = true;
		if (countFinish == 27) {
			myTimer.pause();
			m_pScorecard->setTotalLevelTime(myTimer.get_ticks()/1000);
			m_pScorecard->setTotalTimeInAir(m_pPlayer->inAir);
			m_pScorecard->setNumReloads(m_pPlayer->numOfReloads);
			m_pScorecard->setNumCoins(m_pPlayer->numOfCoins);
			m_pScorecard->setNumShots(m_pPlayer->numOfShots);
			countFinish = 0;
			m_pScorecard->saveData(int(activeLevel));
			Engine::Instance().GetFSM().ChangeState(new EndState(activeLevel,activeLevelSet));
		}
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	     {
		myTimer.pause(); 
		m_pScorecard->setTotalLevelTime(myTimer.get_ticks()/1000);
		m_pScorecard->setTotalTimeInAir(m_pPlayer->inAir);
		m_pScorecard->setNumReloads(m_pPlayer->numOfReloads);
		m_pScorecard->setNumCoins(m_pPlayer->numOfCoins);
		m_pScorecard->setNumShots(m_pPlayer->numOfShots);
		countFinish = 0;
		m_pScorecard->saveData(int(activeLevel));
		Engine::Instance().GetFSM().PushState(new PauseState());
		
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
	std::stringstream timeText, scoreText, lastRec,level;


	SDL_RenderCopy(Engine::Instance().GetRenderer(), controls_text, &control_src, &control_dst);

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
	//if (m_pPlayer->finish == true)
	//{

	//	record = myTimer.get_ticks() / 1000;
	//	lastRec << "Last Record:  " << record - (score % 10);

	////	myTimer.start();
	//}
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
	m_pMusic = Mix_LoadMUS("../Assets/Audio/the_cowboys_curse.wav");
	cout << "Entering Title state....." << endl;
	m_pBGTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_bgSrc = { 0, 0, 1024, 768 };
	m_bgDst = { 0 , 0, 1024, 768 };
	
	m_pLogoTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/(Cowboy) Cadet.png");
	m_logoSrc = { 0, 0, 836, 420 };
	m_logoDst = { (1024 / 2) - (836 / 4), 100, 836 / 2, 420 / 2 };

	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_Start.png", { 0,0,600,156 }, { 360,350,300,80 },0,0,false));

	m_vButtons.push_back(new LevelSelectButton("../Assets/Textures/Buttons/Button_Levels.png", { 0,0,600,156 }, { 360,450,300,80 },0,false));

	m_vButtons.push_back(new ExitButton("../Assets/Textures/Buttons/Button_Quit.png", { 0,0,600,156 }, { 360,550,300,80 }, false));
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
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

// Title State Ends

EndState::EndState(int j, int i)
{
	level = j;
	levelset = i;
	m_pLevelsScores = new LevelScore();
	m_pLevelsScores->loadData();
}

void EndState::Enter()
{
	m_pMusic = Mix_LoadMUS("../Assets/Audio/the_cowboys_curse.wav");
	font = TTF_OpenFont("arial.ttf", 25);
	titleFont = TTF_OpenFont("RioGrande.ttf", 40);
	littleSize = TTF_OpenFont("arial.ttf", 15);
	
	Mix_PlayMusic(m_pMusic, -1);
	
	cout << "Entering End state....." << endl;
	m_pTexture[0] = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_pTexture[1] = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/EndBoard.png");
	m_pTexture[2] = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Bar.png");
	int nextLevel = level + 1;
	int nextLevelSet = levelset;
	if (nextLevel > 3)
	{
		nextLevel = 0;
		nextLevelSet++;
	}
	if( nextLevelSet != 3)
	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_Start.png", { 0,0,600,156 }, { 310,560,100,50 },nextLevelSet,nextLevel,false));

	m_vButtons.push_back(new MainMenuButton("../Assets/Textures/Buttons/Button_Quit.png", { 0,0,600,156 }, { 625,560,100,50 }, false));
}



void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		Engine::Instance().GetFSM().ChangeState(new TitleState());
		/*Engine::Instance().getPlayer()->finish = false;*/
	}
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	
	{
		if (m_vButtons[i]!=nullptr)
		{
			m_vButtons[i]->Update();
		}
	}
}

void EndState::Render()
{
	
	SDL_Rect src = { 0, 0, 1024, 768 };
	SDL_Rect dst = { 0 , 0, 1024, 768 };
	SDL_Rect boardsrc = { 0,0,512,512 };
	SDL_Rect boarddst = { 256,128,512,512 };
	SDL_Rect barsrc = { 0, 0, 170, 60 };
	SDL_Rect bardst1 = { 302,290,170,60 };
	SDL_Rect bardst2 = { 562,290,170,60 };
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[0], &src, &dst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[1], &boardsrc, &boarddst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	std::stringstream scoreText;
	scoreText.str("");
	scoreText << "" << m_pLevelsScores->m_vLevelsScores[level]->getTotalLevelTime();      //level time
	SDL_Color color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font, scoreText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 385, 294, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst1);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	std::stringstream levelText;
	levelText.str("");
	levelText << GameData::Instance()->getLevelSet(levelset)->getDatum(level)->getName();
	color = { 41, 14, 1 };
	surface = TTF_RenderText_Solid(titleFont, levelText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 512 - static_cast<int>(texW * 0.5), 175, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);



	std::stringstream timeText;
	timeText.str("");
	timeText << "" << m_pLevelsScores->m_vLevelsScores[level]->getNumCoins(); ///coins
	color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font, timeText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 510, 540, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	std::stringstream reloadText;
	reloadText.str("");
	reloadText << "" << m_pLevelsScores->m_vLevelsScores[level]->getNumReloads();  ///number of reloads
	color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font, reloadText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 630, 430, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	std::stringstream shootText;
	shootText.str("");
	shootText << "" << m_pLevelsScores->m_vLevelsScores[level]->getNumShots();  ///number of shoots
	color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font, shootText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 385, 430, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);

	std::stringstream airText;
	airText.str("");
	if(m_pLevelsScores->m_vLevelsScores[level]->getTotalTimeInAir()<1000)
	airText << "" << m_pLevelsScores->m_vLevelsScores[level]->getTotalTimeInAir() ;  ///air time
	else
	airText << "" << m_pLevelsScores->m_vLevelsScores[level]->getTotalTimeInAir()/1000;
	color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font, airText.str().c_str(), color);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
	texW = 0;
	texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dstrect = { 630, 294, texW, texH };
	SDL_FreeSurface(surface);
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);
	
	if (m_pLevelsScores->m_vLevelsScores[level]->getTotalTimeInAir() < 1000)
	{
		std::stringstream msText;
		msText.str(" ms");

		color = { 255, 255, 255 };
		surface = TTF_RenderText_Solid(littleSize, msText.str().c_str(), color);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surface);
		texW = 0;
		texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		dstrect = { 675, 301, texW, texH };
		SDL_FreeSurface(surface);
		//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pTexture[2], &barsrc, &bardst2);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), texture, NULL, &dstrect);
	}
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting End state....." << endl;
	Mix_FreeMusic(m_pMusic);
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

LevelSelect::LevelSelect(int i)
{
	level_set = i;
	loadPreviews();
	loadButtons();
}

void LevelSelect::loadPreviews()
{
	switch (level_set)
	{
	case 0:
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level1-1.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level1-2.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level1-3.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level1-4.png"));
		break;
	case 1:
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level2-1.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level2-2.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level2-3.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level2-4.png"));
		break;
	case 2:
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level3-1.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level3-2.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level3-3.png"));
		m_pLevels.push_back(IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/LevelSelect/Level3-4.png"));
		break;
	}
}

void LevelSelect::loadButtons()
{

	switch(level_set)
	{
	case 0:
		m_vButtons.push_back(new LevelSelectButton("../Assets/Textures/Buttons/Level set button.png", { 0,0,124,60 }, { 900,350,124,60 }, 1, false));
		break;
	case 1:
		m_vButtons.push_back(new LevelSelectButton("../Assets/Textures/Buttons/Level set button.png", { 0,0,124,60 }, { 0,350,124,60 }, 0, true));
		m_vButtons.push_back(new LevelSelectButton("../Assets/Textures/Buttons/Level set button.png", { 0,0,124,60 }, { 900,350,124,60 }, 2, false));
		break;
	case 2:
		m_vButtons.push_back(new LevelSelectButton("../Assets/Textures/Buttons/Level set button.png", { 0,0,124,60 }, { 0,350,124,60 }, 1, true));
		break;
	}
	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_L1.png", { 0,0,600,156 }, { 200,325,250,60 }, level_set, 0, false));
	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_L2.png", { 0,0,600,156 }, { 600,325,250,60 }, level_set, 1, false));
	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_L3.png", { 0,0,600,156 }, { 200,612,250,60 }, level_set, 2, false));
	m_vButtons.push_back(new PlayButton("../Assets/Textures/Buttons/Button_L4.png", { 0,0,600,156 }, { 600,612,250,60 }, level_set, 3, false));
	m_vButtons.push_back(new MainMenuButton("../Assets/Textures/Buttons/Button_Mainmenu.png", { 0,0,600,156 }, { 360,680,300,80 }, false));
}

void LevelSelect::Enter()
{
	GameData::Instance()->LoadFromXML();
	m_pMusic = Mix_LoadMUS("../Assets/Audio/the_cowboys_curse.wav");
	m_pBGTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Title_BG.png");
	m_bgSrc = { 0, 0, 1024, 768 };
	m_bgDst = { 0 , 0, 1024, 768 };

	m_pLogoTex = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Textures/Board.png");
	m_logoSrc = { 0, 0, 512, 512 };
	m_logoDst = { 128,64,768,634 };


	
	Mix_PlayMusic(m_pMusic, -1);
}

void LevelSelect::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Update();
	}
}

void LevelSelect::Render()
{
	
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGTex, &m_bgSrc, &m_bgDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pLogoTex, &m_logoSrc, &m_logoDst);
	//SDL_RenderClear(Engine::Instance().GetRenderer());

	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 220, 125, 200, 200 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);*/

	displayPreviews();

	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void LevelSelect::displayPreviews()
{
	tempSrc = { 0,0,200 ,200 };
	tempDst[0] =  { 225, 112, 200, 200 };
	tempDst[1] = { 625, 112, 200, 200 };
	tempDst[2] = { 225, 400, 200, 200 };
	tempDst[3] = { 625, 400, 200, 200 };

	for (int i = 0; i < 4; i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pLevels[i], &tempSrc, &tempDst[i]);
	}
}



void LevelSelect::Exit()
{
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
	m_pLevels.clear();
	m_pLevels.shrink_to_fit();
}
