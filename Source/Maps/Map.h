#ifndef MAP_H
#define MAP_H

#include <string>
#include "Room.h"
#include "../Base/Entity.h"
#include "../Characters/Player.h"
#include <SDL2/SDL.h>

/*
A map represents a set of rooms displayed one at a time (or one centered
in the view and the others black or greyed).
The initial room is always the first room in the (non empty) array 'rooms'.
*/
class Map : public Entity
{
protected:
	/* Array of pointers to rooms */
	Room ** rooms;
	Player &player;
	int roomCount;
	int currentRoom;

public:
	Map(Player& p, int roomCount);
	Map(Player& p, string file);
	virtual ~Map();
	virtual void render(SDL_Renderer * renderer);
	virtual void tick(int time);

	Map& operator=(const Map& that)
	{
		if (this != &that)
		{
			rooms = new Room*[roomCount];
			for (int i = 0; i < roomCount; i++)
			{
				rooms[i] = that.rooms[i];
			}
			roomCount = that.roomCount;
			currentRoom = that.currentRoom;
			player = that.player;
		}
		return *this;
	}
	
	int getRoomCount();
	Room** getRooms();
};

#endif
