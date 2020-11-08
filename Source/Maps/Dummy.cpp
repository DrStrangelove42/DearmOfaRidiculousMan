/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player& p, RenderContext& renderer) : Map(p, 3)
{
	rooms[0] = new DummyRoom(p, renderer, 10, 6);
	rooms[1] = new DummyRoom(p, renderer, 10, 3, 7, 6);
	rooms[2] = new DummyRoom(p, renderer, 4, 15, 3, 6);

	rooms[0]->replaceBlock(new WarpBlock(4, 5, player, "grass", renderer, 1, 1, 1));
	rooms[0]->replaceBlock(new WarpBlock(5, 5, player, "floor", renderer, 2, 1, 1));
	p.teleport(2, 2);
}

DummyRoom::DummyRoom(Player& p, RenderContext& renderer, int wd, int ht, int locX, int locY) : Room(wd, ht, p, renderer)
{


	for (int i = 0; i < w; i++)
	{
		replaceBlock(new StoneWallBlock(i, 0, player, renderer));
		replaceBlock(new StoneWallBlock(i, h - 1, player, renderer));

		if (i == 0 || i == w - 1)
		{
			for (int j = 0; j < h; j++)
			{
				replaceBlock(new StoneWallBlock(i, j, player, renderer));
			}
		}
		else
		{
			for (int j = 0; j < h; j++)
			{
				replaceBlock(new FloorBlock(i, j, player, renderer));
			}

		}
	}

	for (int i = 2; i < w; i++)
	{
		for (int j = 2; j < h; j += 10)
		{
			replaceBlock(new WallBlock(i, j, player, renderer));
		}
	}

	x = locX;
	y = locY;
	discovered = true;
}
