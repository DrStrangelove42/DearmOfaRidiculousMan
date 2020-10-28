#include "Room.h"

Room::Room(int width, int height, Player p, SDL_Renderer* renderer) : w(width), h(height), player(p)
{
	blocks = new Block * [w];

	for (int i = 0; i < w; i++)
	{
		blocks[i] = new Block[h];
		for (int j = 0; j < h; j++)
		{
			printf("init %d %d\n", i, j);
			blocks[i][j] = Block(i, j, player, "bush", renderer);
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
		for (int j = 0; j < h; j++)
		{
			blocks[i][j].render(renderer);
		}
	}
}