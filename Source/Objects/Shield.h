#ifndef SHIELD_H
#define SHIELD_H

#include "PickableObject.h"
#include "VisibleWearable.h"

using namespace std;

/// <summary>
/// A Shield is an Object that can increase the Player's <see cref="Player::defense">defense</see> when picked up.
/// </summary>
class Shield : public PickableObject, public VisibleWearable
{
protected:
	/// <summary>
	/// Defense characteristic, makes the player's defense stronger when picked up.
	/// </summary>
	int defense;
public:

	int getDefense() const;
	/// <summary>
	/// Initialises a new Shield with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="defense"></param>
	Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense);

	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Shield(string headerline, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// We encode a shield with the identifier followed by the defense parameter.
	/// </summary>
	string objectToString() const;

	/*Wearable object implementation*/
	/// <summary>
	/// Called when the user chooses to wear the object. See the remove function to undo the equip action below.
	/// </summary>
	/// <param name="p"></param>
	virtual void equip(Player* p);

	/// <summary>
	/// Called when the player puts off the object.
	/// </summary>
	/// <param name="p"></param>
	virtual void remove(Player* p);
};

#endif
