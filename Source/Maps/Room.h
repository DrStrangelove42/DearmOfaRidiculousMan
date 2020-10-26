#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../Base/Entity.h"
class Room : public Entity
{
protected:
	Block ** blocks;
	int w;
	int h;
	Map container;
public:
	Room(int width, int height, Map map);
	~Room();
	void render(SDL_Renderer renderer)
};


#endif
