#ifndef DUMMY
#define DUMMY

#include "Map.h"
#include "../Characters/Player.h"
#include "../Blocks/WallBlock.h"
class DummyMap : public Map
{
public:
	DummyMap(Player& p, SDL_Renderer* renderer);
};

class DummyRoom : public Room
{
public:
	DummyRoom(Player& p, SDL_Renderer* renderer);
};

#endif