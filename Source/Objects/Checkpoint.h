#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "Object.h"

class Checkpoint : public Object
{
public:
	/*Destructor*/
	virtual ~Checkpoint();

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
	Checkpoint(string identifier, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// Interaction with the game.
	/// </summary>
	/// <param name="game"></param>
	/// <returns>True if the object needs to be removed</returns>
	bool updateObject(GAME* game);
};

#endif
