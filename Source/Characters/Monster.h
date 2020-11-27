#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "../Base/game.h"
#include "MovingEntity.h"
#include "LivingEntity.h"
#include "Player.h"


using namespace std;

class Room;

/// <summary>
/// 
/// </summary>
class Monster : public MovingEntity, public LivingEntity
{
protected:
	/// <summary>
	/// 
	/// </summary>
	int attackValue;
	/// <summary>
	/// 
	/// </summary>
	Player& player;
	/// <summary>
	/// 
	/// </summary>
	int attackDelay;
	/// <summary>
	/// 
	/// </summary>
	int attackRadius;
	/// <summary>
	/// 
	/// </summary>
	int alarmRadius;
	/// <summary>
	/// 
	/// </summary>
	int moveDelay; 
	/// <summary>
	/// 
	/// </summary>
	bool alarmed;
	/// <summary>
	/// 
	/// </summary>
	Texture* texture;
	/// <summary>
	/// 
	/// </summary>
	Room& room;
public:
	/// <summary>
	/// Creates a new monster.
	/// </summary>
	/// <param name="renderer">The rendering context.</param>
	/// <param name="p">The current player.</param>
	/// <param name="r">A reference to the room containing the monster.</param>
	/// <param name="textureId">Texture file id to load.</param>
	/// <param name="health">The max health of the monster.</param>
	/// <param name="dmg">Damage level.</param>
	/// <param name="atkDelay">Delay, in millisecond, between each attack round.</param>
	/// <param name="atkRadius">Attack range.</param>
	/// <param name="coins">Coins owned by the monster.</param>
	/// <param name="exp">Experience given to the player when the monster die.</param>
	/// <param name="moveDelay">Delay, in millisecond, between each move.</param>
	/// <param name="alarmed">If the monster is initially alarmed.</param>
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

	/// <summary>
	/// Go on an attack round.
	/// </summary>
	virtual void attackRound();

	/// <summary>
	/// Alarms the monster if necessary.
	/// </summary>
	virtual void manageAlarm();

	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void kill();
	virtual void tick(int time, RenderContext& r, GAME* game);
};

#endif
