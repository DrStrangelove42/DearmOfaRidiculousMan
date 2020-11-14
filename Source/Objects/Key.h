#ifndef KEY_H
#define KEY_H

#include "Object.h"

class Key : public Object
{
public:
	/*Destructor*/
	~Key();
	
	/*Constructor, a key's identifier should be the letter k followed by a word w, the key can only unlock doors starting with dw*/
	Key(string identifier, int posx, int posy, Player& p, RenderContext& renderer);

	/* How does a key interact with the player? */
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
};

#endif
