#ifndef KEY_H
#define KEY_H

#include "Object.h"

class Key : public Object
{
private:
	/*Each key has a unique character as an identifier, and the key can unlock a door iff they have the same identifier. */
	char id;
public:
	/*Constructor*/
	Key(char identifier, int posx, int posy, Player& p, RenderContext& renderer);
	char getId();
};

#endif
