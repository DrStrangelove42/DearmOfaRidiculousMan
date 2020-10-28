#ifndef MAP_H
#define MAP_H

#include <string>
#include "Room.h"
#include "../Base/Entity.h"
#include "../Characters/Player.h"
#include <SDL2/SDL.h>

class Map : public Entity
{
protected:
	Room * rooms;
	Player player;
	int roomCount;
	int currentRoom;

public:
	Map(Player p, int roomCount);
	Map(Player p, string file);
	~Map();
	void render(SDL_Renderer *  renderer);
	void tick(int time);
};

#endif
