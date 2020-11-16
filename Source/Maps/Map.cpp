#include "Map.h"

Map::Map(Player& p, int roomCount) : player(p), roomCount(roomCount), currentRoom(0)
{
	rooms = new Room* [roomCount];
}

Map::~Map()
{
	for (int i = 0; i < roomCount; i++)
	{
		delete rooms[i];
	}
	delete[] rooms;
}

Map::Map(string filename, string ext, Player& p, RenderContext& renderer, int startMap, int startRoom) : player(p)
{
  mapFromFiles(filename, ext, p, renderer, startMap, startRoom);
}

void Map::render(RenderContext& renderer, int offsetX, int offsetY)
{
	Room* cur = rooms[currentRoom];

	int offX = offsetX - cur->getX() + (BLOCKS_W - cur->getW()) / 2;
	int offY = offsetY - cur->getY() + (BLOCKS_H - cur->getH()) / 2;

	cur->render(renderer, offX, offY);

	for (int i = 0; i < roomCount; i++)
	{
		if (i != currentRoom)
		{
			rooms[i]->render(renderer, offX, offY);
		}
	}

	player.render(renderer, offX + cur->getX(), offY + cur->getY());
}

void Map::tick(int time)
{
	rooms[currentRoom]->tick(time);
}

Room** Map::getRooms()
{
	return rooms;
}

int Map::getCurrentRoom()
{
  return currentRoom;
}

void Map::onKeyDown(EVENT_ARGS * ea)
{
	rooms[currentRoom]->onKeyDown(ea);
}
