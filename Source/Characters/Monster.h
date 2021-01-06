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
	int lastTimeAtk = 0;
	int lastTimeMv = 0;

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
	/// Pointer because sometimes the room changes.
	/// </summary>
	Room* room;

	/// <summary>
	/// If the monster have been killed.
	/// </summary>
	bool killed;

	/// <summary>
	/// The string of length 1 that represents the type of monster.
	/// </summary>
	string type;
public:
	virtual ~Monster() { cout << "delete monster" << endl; }
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
		Room* r,
		string textureId,
		int health,
		int dmg,
		int atkDelay = 1000,
		int atkRadius = 1,
		int coins = 200,
		int exp = 50,
		int moveDelay = 500,
		bool alarmed = false, int defense = 0);

	/// <summary>
	/// Go on an attack round.
	/// </summary>
	virtual void attackRound();

	/// <summary>
	/// Alarms the monster if necessary.
	/// </summary>
	virtual void manageAlarm();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;

	/// <summary>
	/// 
	/// </summary>
	virtual void kill();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// Change room in which the monster resides.
	/// </summary>
	/// <param name="r"></param>
	void setRoom(Room* r);

	string monsterToString() const;
};

#endif
