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

class Room;

class Monster : public MovingEntity, public LivingEntity
{
protected:
	int attackValue;
	Player& player;
	
	int attackDelay;
	int attackRadius;
	int alarmRadius;
	int moveDelay; 
	bool alarmed;
	Texture* texture;

	Room& room;
public:
	
	Monster(RenderContext& renderer,
		Player& p,
		Room& r,
		string textureId,
		int health,
		int dmg,
		int atkDelay = 1000,
		int atkRadius = 1,
		int coins = 200,
		int exp = 50,
		int moveDelay = 500,
		bool alarmed = false );
	virtual void attackRound();
	virtual void manageAlarm();
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void kill();
	virtual void tick(int time, RenderContext& r);
};

#endif
