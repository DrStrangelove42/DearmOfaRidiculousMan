#ifndef SWORD_H
#define SWORD_H

#include "PickableObject.h"
#include "VisibleWearable.h"

using namespace std;

/// <summary>
/// A Sword is an Object that can increase the Player's <see cref="Player::attack">attack</see> when picked up.
/// </summary>
class Sword : public VisibleWearable
{
protected:

	/// <summary>
	/// Attack characteristic, makes the player's attacks stronger when picked up.
	/// </summary>
	int attack;
public: 
	Sword(const Sword& other) : VisibleWearable(other), attack(other.attack) {}

	/// <summary>
	/// In order to be deep-copied (for ex. in a shop),
	/// PickableObjects and all of its derivatives should
	/// implement a clone() function to keep the polymorphic
	/// object in the correct type. To copy the derivated
	/// instance, use* ->clone().
	/// </summary>
	/// <returns></returns>
	virtual Sword* clone() const {
		return new Sword(*this);
	}

	int getAttack() const;
	/// <summary>
	/// Initialises a new Sword with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="attack"></param>
	Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack);

	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Sword(string headerline, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// We encode a sword with sw followed by the attack parameter.
	/// </summary>
	string objectToString() const;

	/*Wearable object implementation*/
	/// <summary>
	/// Called when the user chooses to wear the object. See the remove function to undo the equip action below.
	/// </summary>
	/// <param name="p"></param>
	virtual void equip(Player* p)const;

	/// <summary>
	/// Called when the player puts off the object.
	/// </summary>
	/// <param name="p"></param>
	virtual void remove(Player* p)const;

	/// <summary>
	/// Specific info for a sword
	/// </summary>
	/// <returns></returns>
	virtual string getInfo() const;
};

#endif
