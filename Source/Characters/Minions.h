#ifndef MINIONS_H
#define MINIONS_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"
#include "LivingEntity.h"

class Minions : public MovingEntity, public LivingEntity
{
protected:
	Texture * texture;
public:
	Minions(RenderContext& renderer);
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void kill();
	virtual void tick(int time);
};

#endif
