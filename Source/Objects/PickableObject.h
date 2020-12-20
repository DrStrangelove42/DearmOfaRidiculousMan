#ifndef PICKABLEOBJ_H
#define PICKABLEOBJ_H

#include "Object.h"

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
	PickableObject(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, int attack = 0, int defense = 0);
 
	/// <summary>
	/// How does a key interact with the player?
	/// </summary>
	/// <param name="game"></param>
	bool updateObject(GAME* game);
};

#endif
