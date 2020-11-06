#include "Map.h"

Map::Map(Player& p, int roomCount) : player(p), roomCount(roomCount), currentRoom(0)
{
	rooms = new Room * [roomCount];
}

Map::~Map()
{
	for (int i = 0; i < roomCount; i++)
	{
		delete rooms[i];
	}
	delete[] rooms;
}

Map::Map(Player& p, string file) : player(p)
{
	//TODO : decode a map file.
}

void Map::render(SDL_Renderer* renderer)
{
	rooms[currentRoom]->render(renderer);
}

void Map::tick(int time)
{
	rooms[currentRoom]->tick(time);
}

int Map::getRoomCount()
{
	return roomCount;
}

Room** Map::getRooms()
{
	return rooms;
}
