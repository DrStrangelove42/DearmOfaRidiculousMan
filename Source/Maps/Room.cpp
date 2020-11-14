#include "Room.h"

Room::Room(int width, int height, Player& p, RenderContext& renderer) : w(width), h(height), player(p), discovered(false)
{
	if (w > 0 && h > 0)
	{
		blocks = new Block * *[width];

		for (int i = 0; i < w; i++)
		{
			blocks[i] = new Block * [h];
			for (int j = 0; j < h; j++)
			{
				blocks[i][j] = new Block(i, j, "empty", renderer);
			}
		}
	}
	objects = unordered_map<Object, string>();
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
	for (auto& entry : objects)
	{
		cout << "Freeing " << entry.first << endl;
		delete entry.second;
	}
}

void Room::render(RenderContext& renderer, int offsetX, int offsetY)
{
	if (discovered)
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

void Room::addObject(Object object)
{
        string id=object.getId();
        if (objects.find(id) == objects.end())
        {
		objects[id] = object;
		blocks[object.getX()][object.getY()]->setTrav(object.getTrav());
	}
	else
	{
	        cout << "Two objects have the same identifier " << id << endl;
	}
}

void Room::tick(int time)
{
	//TODO
}

void Room::replaceBlock(Block* newBlock)
{
	int i = newBlock->getX();
	int j = newBlock->getY();

	if (i < w && j < h)
	{
		delete blocks[i][j];
		blocks[i][j] = newBlock;
	}
}

Block* Room::getCurrentBlock()
{
	return blocks[player.getX()][player.getY()];
}

void Room::onKeyDown(EVENT_ARGS* ea)
{
	int curX = player.getX();
	int curY = player.getY();
	/*
	We transfer the event to the destination block. It decides if the
	player moves by itself.
	*/
	switch (ea->key)
	{
	case Up:
	        if (curY > 0 && blocks[curX][curY - 1]->getTrav())
		        player.teleport(curX, curY - 1);
		break;
	case Left:
	        if (curX > 0 && blocks[curX - 1][curY]->getTrav())
		        player.teleport(curX - 1, curY);
		break;
	case Right:
	        if (curX < w - 1 && blocks[curX + 1][curY]->getTrav())
		        player.teleport(curX + 1, curY);
		break;
	case Down:
	        if (curY < h - 1 && blocks[curX][curY + 1]->getTrav())
		        player.teleport(curX, curY + 1);
		break;
	default:
		break;
	}
}
