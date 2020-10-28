#include "Map.h"


Map::Map(Player p, int roomCount) : player(p), roomCount(roomCount), currentRoom(0)
{

}

Map::~Map()
{
	/*Free memory*/
}

Map::Map(Player p, string file) : player(p)
{

}

void Map::render(SDL_Renderer* renderer)
{
	rooms[currentRoom].render(renderer);
}

void Map::tick(int time)
{
	rooms[currentRoom].tick(time);
}