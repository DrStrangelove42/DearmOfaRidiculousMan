#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"
#include "LivingEntity.h"

using namespace std;

class Monster : public MovingEntity, public LivingEntity
{
protected:
	int damage;
	Texture* texture;
public:
	Monster(RenderContext& renderer, string textureId, int dmg);

	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void kill();
	virtual void tick(int time);
};

#endif
