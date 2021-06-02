#ifndef WEARABLE_H
#define WEARABLE_H

#include "PickableObject.h"
#include "../Characters/Player.h"

/// <summary>
/// An Object is an Entity that can be found in a Room, for the Player to interact with, in a Chest (which is an Object in and of itself), for the Player to collect, or in a Player's inventory, for the Player to use.
/// </summary>
class Wearable : public PickableObject
{
protected:

public:
	virtual ~Wearable();

	Wearable(const Wearable& other) : PickableObject(other) {}

	virtual Wearable* clone() const {
		return new Wearable(*this);
	}

	Wearable(string identifier, int posx, int posy, string tx, RenderContext& renderer);

	/// <summary>
	/// Called when the user chooses to wear the object. See the remove function to undo the equip action below.
	/// </summary>
	/// <param name="p"></param>
	virtual void equip(Player* p)const {}

	/// <summary>
	/// Called when the player puts off the object.
	/// </summary>
	/// <param name="p"></param>
	virtual void remove(Player* p)const {}

	/// <summary>
	/// Returns a value indicating the status of the object.
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	virtual bool isWorn(Player* p)const { return false; }
};

#endif
