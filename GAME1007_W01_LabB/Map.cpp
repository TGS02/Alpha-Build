#include "Map.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include <SDL.h>

int bgMapArr[8][8] = {
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1} };

int mapArr[24][32] = {
{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,5,14,0,0,0,0,5},
{5,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,0,0,5},
{5,13,13,13,14,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,5,21,21,21,2,13,13,13,13,2,2,2,0,0,0,0,0,0,0,16,0,0,5},
{5,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,5,5,0,0,0,0,0,0,0,16,0,0,5},
{5,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,2,2,2,2,0,0,12,13,13,13,5},
{5,2,2,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,5},
{5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,5},
{5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,16,5,5,2,2,0,0,0,0,5},
{5,5,5,13,13,14,0,0,0,0,0,12,13,2,13,14,0,0,0,2,13,13,13,13,5,5,5,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,33,5,34,0,0,0,33,5,34,0,0,0,33,5,5,34,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,32,0,0,0,0,0,32,32,0,0,0,0,5},
{5,0,0,0,0,0,12,14,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,0,5},
{5,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,0,5},
{5,2,2,2,2,2,0,0,0,0,0,0,2,5,2,0,0,0,0,12,13,13,13,14,0,0,2,2,2,2,2,5},
{5,5,5,5,5,5,34,12,14,0,0,0,32,32,32,0,0,0,0,0,0,0,0,0,0,33,5,5,5,5,5,5},
{5,5,5,5,5,5,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,5,5,5,5,5,5},
{5,5,5,5,5,5,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,5,5,5,5,5,5},
{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
};

int ColMapArr[24][32] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,2,0,0,0,0,1},
{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,1},
{1,2,2,2,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,4,4,4,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0,1,0,0,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,2,2,2,2,1},
{1,1,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1},
{1,1,1,2,2,2,0,0,0,0,0,2,2,1,2,2,0,0,0,1,2,2,2,2,1,1,1,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,6,1,3,0,0,0,6,1,3,0,0,0,6,1,1,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,7,0,0,0,0,0,7,7,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,1},
{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,2,2,2,2,2,0,0,1,1,1,1,1,1},
{1,1,1,1,1,1,3,2,2,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,6,1,1,1,1,1,1},
{1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,1,1,1,1,1},
{1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map(SDL_Renderer* m_pRenderer)
{
	background_1 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Background_1.png");
	tile2 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile2.png");
	tile3 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile3.png");
	tile5 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile5.png");
	tile12 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile12.png");
	tile13 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile13.png");
	tile1 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile1.png");
	tile14 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile14.png");
	tile15 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Tile15.png");
	acid1 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Acid1.png");
	acid2 = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Acid2.png");
	box = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Box.png");
	spike_up = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Spike_Up.png");
	spike_down = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Spike_Down.png");
	spike_left = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Spike_Left.png");
	spike_right = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Spike_Right.png");
	exit_bottom = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Exit_Bottom.png");
	exit_top = TextureManager::LoadTexture(m_pRenderer, "../Assets/Textures/Exit_Top.png");
	src.x = src.y = 0;
	src.w = dst.w = 32;
	src.h = dst.h = 32;
	dst.x = dst.y = 0;
	src_bg = { 0,0,1008,276 };
	dst_bg = { 0,0,1008/2,276/2 };
	loadBG(bgMapArr);
	loadMap(mapArr);
	checkColMap(ColMapArr);
}

Map::~Map()
{

}

void Map::checkColMap(int arr[24][32])
{
	for (int row = 0; row < 24; row++)
		for (int column = 0; column < 32; column++)
		{
			colMap[row][column] = ColMapArr[row][column];
		}
}

void Map::loadMap(int arr[24][32])
{
	for (int row = 0; row < 24; row++)
		for (int column = 0; column < 32; column++)
		{
			map[row][column] = arr[row][column];
		}
}

void Map::loadBG(int arr[8][8])
{
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			map_bg[row][column] = arr[row][column];
		}
}

void Map::DrawMap(SDL_Renderer* g_pRenderer, vector<int> numTile)
{
	int type = 0;
	for (int row = 0; row < 24; row++)
	{
		for (int column = 0; column < 32; column++)
		{
			type = map[row][column];
			dst.x = column * 32;
			dst.y = row * 32;
			for (int i = 0; i < numTile.size(); i++)
			{
				if (type == numTile[i]) {
					switch (type)
					{
					case 0:
						break;
					case 1:
						TextureManager::Draw(g_pRenderer, tile1, &src, &dst);
						break;
					case 2:
						TextureManager::Draw(g_pRenderer, tile2, &src, &dst);
						break;
					case 3:
						TextureManager::Draw(g_pRenderer, tile3, &src, &dst);
						break;
					case 5:
						TextureManager::Draw(g_pRenderer, tile5, &src, &dst);
						break;
					case 12:
						TextureManager::Draw(g_pRenderer, tile12, &src, &dst);
						break;
					case 13:
						TextureManager::Draw(g_pRenderer, tile13, &src, &dst);
						break;
					case 14:
						TextureManager::Draw(g_pRenderer, tile14, &src, &dst);
						break;
					case 15:
						TextureManager::Draw(g_pRenderer, tile15, &src, &dst);
						break;
					case 16:
						TextureManager::Draw(g_pRenderer, box, &src, &dst);
						break;
					case 21:
						SDL_SetTextureAlphaMod(acid1, 128);
						TextureManager::Draw(g_pRenderer, acid1, &src, &dst);
						break;
					case 22:
						SDL_SetTextureAlphaMod(acid2, 128);
						TextureManager::Draw(g_pRenderer, acid2, &src, &dst);
						break;
					case 31:
						TextureManager::Draw(g_pRenderer, spike_up, &src, &dst);
						break;
					case 32:
						TextureManager::Draw(g_pRenderer, spike_down, &src, &dst);
						break;
					case 33:
						TextureManager::Draw(g_pRenderer, spike_left, &src, &dst);
						break;
					case 34:
						TextureManager::Draw(g_pRenderer, spike_right, &src, &dst);
						break;
					case 41:
						TextureManager::Draw(g_pRenderer, exit_bottom, &src, &dst);
						break;
					case 42:
						TextureManager::Draw(g_pRenderer, exit_top, &src, &dst);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void Map::DrawBG(SDL_Renderer* g_pRenderer, vector<int> numTile)
{
	int type = 0;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			type = map_bg[row][column];
			dst_bg.x = column * 1008/2;
			dst_bg.y = row * 276/2;
			for (int i = 0; i < numTile.size(); i++)
			{
				if (type == numTile[i]) {
					switch (type)
					{
					case 1:
						TextureManager::Draw(g_pRenderer, background_1, &src_bg, &dst_bg);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void Map::update(int round)
{

}

string Map::checkMiddlePlatforms(int tmpRow, int tmpCol)
{
	string pos;
	if (map[tmpRow][tmpCol - 1] != 0 && map[tmpRow][tmpCol + 1] == 0)
		return "left";
	else if (map[tmpRow][tmpCol - 1] == 0 && map[tmpRow][tmpCol + 1] != 0)
		return "right";
	else if (map[tmpRow][tmpCol - 1] != 0 && map[tmpRow][tmpCol + 1] != 0)
		return  "both";
	else return  "none";



}

void Map::clean()
{
	SDL_DestroyTexture(tile1);
	SDL_DestroyTexture(tile2);
	SDL_DestroyTexture(tile3);
	SDL_DestroyTexture(tile5);
	SDL_DestroyTexture(tile12);
	SDL_DestroyTexture(tile13);
	SDL_DestroyTexture(tile14);
	SDL_DestroyTexture(tile15);
	SDL_DestroyTexture(box);
	SDL_DestroyTexture(acid1);
	SDL_DestroyTexture(acid2);
	SDL_DestroyTexture(spike_down);
	SDL_DestroyTexture(spike_up);
	SDL_DestroyTexture(spike_left);
	SDL_DestroyTexture(spike_right);
	SDL_DestroyTexture(exit_bottom);
	SDL_DestroyTexture(exit_top);
	SDL_DestroyTexture(background_1);
}
