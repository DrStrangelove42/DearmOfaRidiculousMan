#ifndef PICKABLEOBJ_H
#define PICKABLEOBJ_H

#include "Object.h"

class Player;

/// <summary>
/// A PickableObject is a type of Object that can be picked up by the Player when walked upon.
/// </summary>
class PickableObject : public Object
{
public:
	/*Destructor*/
	virtual ~PickableObject();

	PickableObject(const PickableObject& other);

	/// <summary>
	/// In order to be deep-copied (for ex. in a shop),
	/// PickableObjects and all of its derivatives should
	/// implement a clone() function to keep the polymorphic
	/// object in the correct type. To copy the derivated
	/// instance, use* ->clone().
	/// </summary>
	/// <returns></returns>
	virtual PickableObject* clone() const {
		return new PickableObject(*this);
	}

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
	PickableObject(string identifier, int posx, int posy, string tx, RenderContext& renderer);

	/// <summary>
	/// Interaction with the game.
	/// </summary>
	/// <param name="game"></param>
	/// <returns>True if the object needs to be removed</returns>
	bool updateObject(GAME* game);

	/// <summary>
	/// Called when the object is picked up.
	/// </summary>
	virtual void onPickup(Player* p) const;
};

#endif
