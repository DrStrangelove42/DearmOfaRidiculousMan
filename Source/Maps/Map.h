#ifndef MAP_H
#define MAP_H

#include <string>

#include "../Base/Entity.h"

class Map : public Entity
{
protected:
	Room rooms[];
public:
	Map();
	Map(string file);
	void render(SDL_Renderer renderer);
	void tick(int time);
};

#endif
