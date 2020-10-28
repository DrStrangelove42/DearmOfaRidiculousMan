/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player p, SDL_Renderer* renderer) : Map(p, 1)
{
	rooms = new Room[1]{ DummyRoom(p, renderer) };
}

DummyRoom::DummyRoom(Player p, SDL_Renderer *renderer) : Room(20, 30, p, renderer)
{
	for (int x = 4; x < 15; x++)
	{
		for (int y = 2; y < 20; y += 10)
		{
			//blocks[x][y] = WallBlock(x, y, player, renderer);
		}
	}
}