/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player& p, RenderContext& renderer) : Map(p, 3)
{
	rooms[0] = new DummyRoom(p, renderer, 10, 6);
	rooms[1] = new DummyRoom(p, renderer, 10, 3, 7, 6);
	rooms[2] = new DummyRoom(p, renderer, 4, 15, 3, 6);

	rooms[0]->addObject(Warp("",2,1,0,4, 5, "!1", player, renderer));
	/*BACK:*/ rooms[2]->addObject(Warp("",0,4,5,1, 0, "!2", player, renderer));
	rooms[0]->addObject(Warp("",2,2,0,5, 5,"!3", player, renderer));
	/*BACK:*/ rooms[2]->addObject(Warp("",0,5,5,2,0,"!4", player, renderer));
	rooms[0]->addObject(Warp("",1,1,0,8,5,"!5", player, renderer));
	/*BACK:*/ rooms[1]->addObject(Warp("",0,8,5,1, 0,"!6", player, renderer));

	
	p.teleport(2, 2);
}

DummyRoom::DummyRoom(Player& p, RenderContext& renderer, int wd, int ht, int locX, int locY) : Room(wd, ht, p, renderer)
{


	for (int i = 0; i < w; i++)
	{
		replaceBlock(new StoneWallBlock(i, 0, renderer));
		replaceBlock(new StoneWallBlock(i, h - 1, renderer));

		if (i == 0 || i == w - 1)
		{
			for (int j = 0; j < h; j++)
			{
				replaceBlock(new StoneWallBlock(i, j, renderer));
			}
		}
		else
		{
			for (int j = 0; j < h; j++)
			{
				replaceBlock(new FloorBlock(i, j, renderer));
			}

		}
	}

	for (int i = 2; i < w; i++)
	{
		for (int j = 2; j < h; j += 10)
		{
			replaceBlock(new WallBlock(i, j, renderer));
		}
	}

	x = locX;
	y = locY;
	discovered = true;
}
