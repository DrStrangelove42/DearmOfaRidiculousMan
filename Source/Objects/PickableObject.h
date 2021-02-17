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
	PickableObject(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav);
 
	/// <summary>
	/// Interaction with the game.
	/// </summary>
	/// <param name="game"></param>
	/// <returns>True if the object needs to be removed</returns>
	bool updateObject(GAME* game);

	/// <summary>
	/// Called when the object is picked up.
	/// </summary>
	virtual void onPickup(Player* p);
};

#endif
