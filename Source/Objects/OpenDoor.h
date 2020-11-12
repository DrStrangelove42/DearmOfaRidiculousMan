#ifndef OPENDOOR_H
#define OPENDOOR_H

#include "Object.h"

class OpenDoor : public Object
{
private:
	/*Each door has a unique character as an identifier, and the door can be unlocked by a key iff they have the same identifier. */
	char id;
public:
	/*Destructor*/
	~OpenDoor()
	
	/*Constructor*/
	OpenDoor(char identifier, int posx, int posy, Player& p, RenderContext& renderer);
	char getId();

	/* How does a door interact with the player? */
	void updateObject(Player& p, RenderContext& renderer);
};

#endif
