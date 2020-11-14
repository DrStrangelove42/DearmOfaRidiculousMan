#ifndef DOOR_H
#define DOOR_H

#include "Object.h"

class Door : public Object
{
public:
	/*Destructor*/
	~Door();
	
	/*Constructor*/
	Door(string identifier, int posx, int posy, Player& p, RenderContext& renderer);

	/* How does a door interact with the player? */
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
};

#endif
