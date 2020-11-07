/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap(Player& p, RenderContext& renderer) : Map(p, 1)
{
	rooms[0] = new DummyRoom(p, renderer);
	p.teleport(2, 2);
} 

DummyRoom::DummyRoom(Player& p, RenderContext& renderer) : Room(4, 5, p, renderer)
{
	for (int x = 2; x < 4; x++)
	{
		for (int y = 2; y < 5; y += 10)
		{
			blocks[x][y] = new WallBlock(x, y, player, renderer);
		}
	}
}
