#ifndef OBJECT_H
#define OBJECT_H


#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"
#include "../Base/game.h"

class Object : public MovingEntity
{
protected:
	/// <summary>
	/// Identifier of the object.
	/// </summary>
	string id;

	/// <summary>
	/// Attack characteristic, makes the player's attacks stronger when picked up.
	/// </summary>
	int attack;
	
	/// <summary>
	/// Defense characteristic, makes the player's defense stronger when picked up.
	/// </summary>
	int defense;

public:
	~Object();

	/// <summary>
	/// Initialises a new Object with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	/// <param name="attack"></param>
	/// <param name="defense"></param>
	Object(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, int attack = 0, int defense = 0);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="other"></param>
	Object(const Object& other);

	/// <summary>
	/// 
	/// </summary>
	bool traversable;

	string getId() const;
	bool getTrav();
	int getAttack();
	int getDefense();

	/// <summary>
	/// Change the object position. 
	/// </summary>
	/// <param name="px"></param>
	/// <param name="py"></param>
	void move(int px, int py);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// </summary>
	/// <param name="game"></param>
	virtual void updateObject(GAME* game);

	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="renderer"></param>
	virtual void tick(int time, GAME* game);

	bool operator== (const Object& otherObj) const
	{
		return otherObj.id == id;
	}
};

/// <summary>
/// Map helpers
/// </summary>
struct ObjectHash
{
	size_t operator()(const Object& o) const
	{
		return hash<string>()(o.getId());
	}
};

#endif
