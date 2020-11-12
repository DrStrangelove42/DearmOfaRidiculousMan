#ifndef KEY_H
#define KEY_H

#include "Object.h"

class Key : public Object
{
private:
	/*Each key has a unique character as an identifier, and the key can unlock a door iff they have the same identifier. */
	char id;
public:
	/*Destructor*/
	~Key();
	
	/*Constructor*/
	Key(char identifier, int posx, int posy, Player& p, RenderContext& renderer);
	char getId();

	/* How does a key interact with the player? */
	void updateObject(Player& p, RenderContext& renderer);
};

#endif
