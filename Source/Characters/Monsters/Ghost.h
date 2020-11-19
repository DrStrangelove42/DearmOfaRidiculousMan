#ifndef GHOST_H
#define GHOST_H

#include "../Monster.h"

/*
We create a type of monster : ghosts. These will always have the same characteristics.
*/
class Ghost : public Monster
{
protected:

public:
	Ghost(RenderContext& renderer, Player& p);
	~Ghost();
};

#endif
