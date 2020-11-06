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
	/* Reference to the player */
	Player &player;
	/* Number of rooms in the map */
	int roomCount;
	/* Index of the room that is currently displayed (in which the player is) */
	int currentRoom;

public:
	/* Creates a new empty map with a pre-allocated array for rooms. */
	Map(Player& p, int roomCount);
	/* Creates a Map object from a map file */
	Map(Player& p, string file);

	/* Std destructor */
	virtual ~Map();
	/* Rendering of the map */
	virtual void render(SDL_Renderer * renderer);
	/* Time management */
	virtual void tick(int time);

	/* Copy-assignment operator */
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
	
	/* Accessors */
	int getRoomCount();
	Room** getRooms();
};

#endif
