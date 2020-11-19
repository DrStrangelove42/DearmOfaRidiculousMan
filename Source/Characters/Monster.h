#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"
#include "LivingEntity.h"
#include "Player.h"

using namespace std;

class Monster : public MovingEntity, public LivingEntity
{
protected:
	int damage;
	Player& player;
	
	int attackDelay;
	int attackRadius;
	int alarmRadius;
	Texture* texture;
public:
	
	Monster(RenderContext& renderer,
		Player& p,
		string textureId,
		int health,
		int dmg,
		int atkDelay = 1000,
		int atkRadius = 1,
		int coins = 200,
		int exp = 50,
		bool alarmed = false );
	virtual void attackRound();
	virtual void alarm();
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void kill();
	virtual void tick(int time, RenderContext& r);
};

#endif
