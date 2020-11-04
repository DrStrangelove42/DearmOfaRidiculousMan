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
	virtual void tick(int time);

	Map& operator=(const Map& that)
	{
		if (this != &that)
		{
			rooms = new Room[roomCount];
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
	Room* getRooms();
};

#endif
