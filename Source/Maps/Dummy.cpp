/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap()
{
	rooms = new Room[1];
	rooms[0] = Room();
	currentRoom = 0;
}

DummyRoom::DummyRoom()
{
	blocks = new Block[20][30];

	for (int x = 4; x < 15; x++)
	{
		for (int y = 2; y < 20; y += 10)
		{
			blocks[x][y] = WallBlock(x, y, map.player);
		}
	}
}