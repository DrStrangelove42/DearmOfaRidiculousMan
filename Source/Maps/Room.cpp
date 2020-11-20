#include "Room.h"

Room::Room(int width, int height, int absx, int absy, Player& p, RenderContext& renderer) : w(width), h(height), x(absx), y(absy), player(p), discovered(false)
{
	srand(time(0));
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

void Room::updateAllObjects(RenderContext& renderer, EVENT_ARGS* ea)
{
	for (auto& entry : objects)
	{
		entry.second->updateObject(player, renderer, ea);
	}
}

void Room::tick(int time, RenderContext& r)
{
	updateAllObjects(r);
	for (Monster* m : monsters)
	{
		static int lastTime = time;
		m->tick(time, r);
		if (time - lastTime >= 1000)
		{

			int r = rand() % 4;
			switch (r)
			{
			case 0:
				tryTeleportAt(*m, m->getX() + 1, m->getY()); break;
			case 1:
				tryTeleportAt(*m, m->getX(), m->getY() + 1); break;
			case 2:
				tryTeleportAt(*m, m->getX() - 1, m->getY()); break;
			case 3:
				tryTeleportAt(*m, m->getX(), m->getY() - 1); break;
			default:
				break;
			}
			lastTime = time;
		}
	}
}

void Room::attackMonsters()
{
	for (Monster* m : monsters)
	{
		if (player.isInAttackRange(m->getX(), m->getY()))
		{
			m->damage(player.getAttack());
		}
	}
}

void Room::addMonster(Monster* m)
{
	monsters.push_back(m);
}

void Room::removeMonster(Monster* m)
{
	monsters.remove(m);
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

void Room::onKeyDown(EVENT_ARGS* ea)
{
	int curX = player.getX();
	int curY = player.getY();

	switch (ea->key)
	{
	case Up:
		curY--;
		break;
	case Left:
		curX--;
		break;
	case Right:
		curX++;
		break;
	case Down:
		curY++;
		break;
	case A:
		//TODO Jump ?
		break;
	case B:
		//Atk
		attackMonsters();
		break;
	default:
		break;
	}

	if (curX != player.getX() || curY != player.getY())
		tryTeleportAt(player, curX, curY);
}
