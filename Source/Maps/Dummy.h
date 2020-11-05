#ifndef DUMMY
#define DUMMY

#include "Map.h"
#include "../Characters/Player.h"
#include "../Blocks/WallBlock.h"
#include "Room.h"
class DummyMap : public Map
{
public:
	DummyMap(Player& p, SDL_Renderer* renderer);
};

class DummyRoom : public Room
{
public:
	DummyRoom(Player& p, Map& m, SDL_Renderer* renderer);
};

#endif