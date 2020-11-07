/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player& p, RenderContext& renderer) : Map(p, 3)
{
	rooms[0] = new DummyRoom(p, renderer);
	rooms[1] = new DummyRoom(p, renderer, 5, 0);
	rooms[2] = new DummyRoom(p, renderer, 3, 6);
	p.teleport(2, 2);
} 

DummyRoom::DummyRoom(Player& p, RenderContext& renderer, int locX, int locY) : Room(5, 6, p, renderer)
{
	for (int x = 2; x < 4; x++)
	{
		for (int y = 2; y < 5; y += 10)
		{
			blocks[x][y] = new WallBlock(x, y, player, renderer);
		}
	}

	for (int x = 0; x < w; x++)
	{
		if (x % w == 0)
		{
			for (int x = 0; x < h; x++)
			{
				blocks[x][y] = new StoneWallBlock(x, y, player, renderer);
			}
		}
	}

	x = locX;
	y = locY;
	discovered = true;
}
