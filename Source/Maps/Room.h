#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../Base/Entity.h"
class Room : public Entity
{
protected:
	Block ** blocks;

public:
	Room(int width, int height);
	void render(SDL_Renderer renderer)
};


#endif
