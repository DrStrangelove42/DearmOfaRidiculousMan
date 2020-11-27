#ifndef MINIONS_H
#define MINIONS_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "Monster.h"

class Minions : public Monster
{
protected:
	Texture * texture;
public:
	//Minions(RenderContext& renderer);
	virtual void kill();
	virtual void tick(int time, GAME* game);
};

#endif
