#include "Room.h"
#include "../Characters/Monsters/Skeleton.h"
#include "../Characters/Monsters/Ghost.h"
#include "./Map.h"

Room::Room(int width, int height, int absx, int absy, Player& p, RenderContext& renderer) :
	w(width), h(height), x(absx), y(absy), player(p), discovered(false), blocks(NULL), breakObjectUpdateLoop(false)
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

void Room::render(RenderContext& renderer, int offsetX, int offsetY)const
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

int Room::getW()const
{
	return w;
}

int Room::getH()const
{
	return h;
}

int Room::getX()const
{
	return x;
}

int Room::getY()const
{
	return y;
}

Block*** Room::getBlocks()
{
	return blocks;
}

list<Monster*>& Room::getMonsters()
{
	return monsters;
}

unordered_map <string, Object*>& Room::getObjects()
{
	return objects;
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
		if (object->getX() < w && object->getY() < h)
			blocks[object->getX()][object->getY()]->setTrav(true);
	}
	else
	{
		delete objects[object->getId()];
		objects[object->getId()] = object;
	}
}

void Room::addObject(Object* object, int x, int y)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((j != 0 || i != 0) && blocks[x + i][y + j]->getTrav())
			{
				object->teleport(x + i, y + j);
				j += 3; i += 3;//make sure to escape the loop
			}
		}
	}
	addObject(object);
}

void Room::stopScanningObjects()
{
	breakObjectUpdateLoop = true;
}

void Room::tick(int time, GAME* game)
{
	list<string>  toDel;
	for (auto& entry : objects)
	{
		if (entry.second->updateObject(game))
		{
			toDel.push_back(entry.first);
		}
		if (breakObjectUpdateLoop)
			break;
	}

	for (string d : toDel)
	{
		objects.erase(d);
	}

	breakObjectUpdateLoop = false;
}

void Room::updateAllMonsters(int time, GAME* game)
{
	if (!discovered) return;

	for (Monster* m : monsters)
	{
		if (m->isAlive())
			m->tick(time, game);
	}

	for (Monster* m : pendingToRemove)
	{
		monsters.remove(m);
	}
	pendingToRemove.clear();

	if (time - lastCleaned >= cleanDelay)
	{
		cleanMonsters();
		lastCleaned = time;
	}
}

void Room::addMonster(Monster* m)
{
	m->setRoom(this);
	monsters.push_back(m);
}

void Room::removeMonster(Monster* m)
{
	monsters.remove(m);
	delete m;
}

void Room::removeObject(string id)
{
	objects.erase(id);
}

void Room::replaceBlock(Block* newBlock)
{
	int i = newBlock->getX();
	int j = newBlock->getY();

	if (i < w && j < h && j >= 0 && i >= 0)
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

void Room::sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft)
{
	for (Monster* m : monsters)
	{
		if (m->isAlive())
			m->sendMonsterToWarp(x, y, destRoom, destX, destY, playerJustLeft);
	}
}

void Room::cleanMonsterWarpInfo()
{
	for (Monster* m : monsters)
	{
		if (m->isAlive())
			m->cleanMonsterWarpInfo();
	}
}

void Room::addMonsterToRemove(Monster* m)
{
	pendingToRemove.push_back(m);
}

string Room::getObjectString(string id)
{
	string toAdd = "";
	auto search = objects.find(id);
	if (search != objects.end())
	{
		toAdd = search->second->objectToString();
	}
	return toAdd;
}
