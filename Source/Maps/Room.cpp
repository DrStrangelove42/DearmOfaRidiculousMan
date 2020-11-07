#include "Room.h"

Room::Room(int width, int height, Player& p, RenderContext& renderer) : w(width), h(height), player(p), discovered(false)
{
	if (w > 0 && h > 0)
	{
		blocks = new Block ** [width];

		for (int i = 0; i < w; i++)
		{
			blocks[i] = new Block*[h];
			for (int j = 0; j < h; j++)
			{
				blocks[i][j] = new Block(i, j, player, "bush", renderer);
			}
		}
	}
}

Room::~Room()
{
	
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			delete blocks[i][j];
		}
		delete[] blocks[i];
	}
	if (w > 0)
	{
		delete[] blocks;
	}
}

void Room::render(RenderContext& renderer, int offsetX, int offsetY)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			blocks[i][j]->render(renderer, offsetX + x, offsetY + y);
		}
	}
}

int Room::getW()
{
	return w;
}

int Room::getH()
{
	return h;
}

int Room::getX()
{
	return x;
}

int Room::getY()
{
	return y;
}

void Room::tick(int time)
{
	//TODO
}