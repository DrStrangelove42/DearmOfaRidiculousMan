#ifndef MAP_H
#define MAP_H

#include <string>

#include "../Base/Entity.h"

class Map : public Entity
{
protected:
	Room * rooms;
	int roomCount;
	int currentRoom;
	Player* player;

public:
	Map(Player* p);
	Map(Player* p, string file);
	~Map();
	void render(SDL_Renderer renderer);
	void tick(int time);
};

#endif
