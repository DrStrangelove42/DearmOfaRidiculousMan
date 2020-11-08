#ifndef DUMMY
#define DUMMY

#include "Map.h"
#include "../Characters/Player.h"
#include "../Blocks/StoneWallBlock.h"
#include "Room.h"

/* This is a demo of a map, for human testing purposes */
class DummyMap : public Map
{
public:
	DummyMap(Player& p, RenderContext& renderer);
};

class DummyRoom : public Room
{
public:
	DummyRoom(Player& p, RenderContext& renderer, int wd, int ht, int locX = 0, int locY = 0);
};

#endif