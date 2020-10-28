#include "Room.h"

Room::Room(int width, int height, Player p, SDL_Renderer* renderer) : w(width), h(height), player(p)
{
	blocks = new Block * [width];

	for (int i = 0; i < width; i++)
	{
		blocks[i] = new Block[height];
		for (int j = 0; j < height; j++)
		{
			blocks[i][j] = Block(i, j, player, "empty", renderer);
		}
	}
}

Room::~Room()
{
	delete blocks;
}

void Room::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; i++)
		{
			//blocks[i][j].render(renderer);
		}
	}
}