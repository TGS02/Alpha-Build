#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class Map
{
public:
	Map(SDL_Renderer* m_pRenderer);
	~Map();
	void loadMap(int arr[24][32]);
	void loadBG();
	void checkColMap(int arr[24][32]);
	void DrawMap(SDL_Renderer* g_pRenderer, std::vector<int> numTile);
	void DrawBG(SDL_Renderer* g_pRenderer, std::vector<int> numTile);
	void update(int round);
	void clean();
	void getFinishFsm(bool finishFSM);
	std::string checkMiddlePlatforms(int tmpRow, int tmpCol);
	int colMap[24][32];
	int map[24][32];
private:
	SDL_Rect src, src1, dst;
	SDL_Rect src_bg, dst_bg;
	SDL_Texture* background_1;
	SDL_Texture* tile2;
	SDL_Texture* tile3;
	SDL_Texture* tile5;
	SDL_Texture* tile12;
	SDL_Texture* tile13;
	SDL_Texture* tile1;
	SDL_Texture* tile14;
	SDL_Texture* tile15;
	SDL_Texture* acid1;
	SDL_Texture* acid2;
	SDL_Texture* box;
	SDL_Texture* spike_up;
	SDL_Texture* spike_down;
	SDL_Texture* spike_left;
	SDL_Texture* spike_right;
	SDL_Texture* exit_bottom;
	SDL_Texture* exit_top;
	SDL_Texture* pickUps1;
	SDL_Texture* pickUps2;
	SDL_Texture* pickUps3;
	SDL_Texture* pickUps4;
	SDL_Texture* pickUps5;
	SDL_Texture* pickUps6;
	SDL_Texture* pickUps7;
	SDL_Texture* pickUps8;
	SDL_Texture* pickUps9;
	int maxSprite,sprite;
	int frame, maxFrame;
	int maxSpriteF, spriteF;
	int framef, maxFrameF;
	int maxSpriteF1, spriteF1;
	int framef1, maxFrameF1;
	void animatePickups();
	int map_bg[24][32];
	bool finish;
};

