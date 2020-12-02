#include "Room.h"
#include "../Characters/Monsters/Skeleton.h"
#include "../Characters/Monsters/Ghost.h"
Room::Room(int width, int height, int absx, int absy, Player& p, RenderContext& renderer) : w(width), h(height), x(absx), y(absy), player(p), discovered(false),blocks(NULL)
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
}

list<Monster*>& Room::getMonsters()
{
	return monsters;
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
	//The objects in the map, which are deep copies of the objects we added, are deleted automatically.
}

void Room::render(RenderContext& renderer, int offsetX, int offsetY)
{
	if (discovered)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				blocks[i][j]->render(renderer, offsetX + x, offsetY + y);
			}
		}
		for (auto& entry : objects)
		{
			entry.second->render(renderer, offsetX + x, offsetY + y);
		}

		for (Monster* m : monsters)
		{
			m->render(renderer, offsetX + x, offsetY + y);
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

Block*** Room::getBlocks()
{
	return blocks;
}

void Room::setDiscovered(bool b)
{
	discovered = b;
}

void Room::cleanMonsters()
{
	list<Monster*> toDel;

	for (Monster* m : monsters)
	{
		if (!m->isAlive())
			toDel.push_back(m);
	}

	for (Monster* d : toDel)
	{
		removeMonster(d);
	}

	toDel.clear();
}

void Room::addObject(Object* object)
{
	if (objects.find(object->getId()) == objects.end())
	{
		objects[object->getId()] = object;
		blocks[object->getX()][object->getY()]->setTrav(true);//TODO
	}
	else
	{
		cout << "Two objects have the same identifier " << object->getId() << endl;
	}
}

void Room::updateAllObjects(GAME* game)
{
	for (auto& entry : objects)
	{
		entry.second->updateObject(game);
	}
}

void Room::tick(int time, GAME* game)
{
	updateAllObjects(game);
	for (Monster* m : monsters)
	{
		if (m->isAlive())
			m->tick(time, game);
	}

	if (time - lastCleaned >= cleanDelay)
	{
		cleanMonsters();
		lastCleaned = time;
	}
}


void Room::addMonster(Monster* m)
{
	monsters.push_back(m);
}

void Room::removeMonster(Monster* m)
{
	monsters.remove(m);
	delete m;
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

void Room::tryTeleportAt(MovingEntity& e, int x, int y)
{
	if (x >= 0 && y >= 0 && x < w && y < h && isTraversable(x, y))
	{
		e.teleport(x, y);
	}
}

bool Room::isTraversable(int mx, int my)
{
	bool tr = blocks[mx][my]->getTrav();

	if (!tr)
		return false;

	for (auto& entry : objects)
	{
		if (entry.second->getX() == mx &&
			entry.second->getY() == my)
		{
			if (!entry.second->getTrav())
				return false;
		}
	}

	return true;
}

void Room::onKeyDown(GAME* game)
{
	player.onKeyDown(game);
}
