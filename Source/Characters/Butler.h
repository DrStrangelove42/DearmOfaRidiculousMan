#ifndef Butler_H
#define Butler_H

#include "NPC.h"

/// <summary>
/// A butler who welcomes the player in the main map.
/// </summary>
class Butler : public NPC
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="speech"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	Butler(string name, string greeting, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// Creates a Butler from a header line in a map file.
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="uniqueId"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Butler(string headerline, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// Returns true if the object has been picked up (thus informing that we should remove it from the room)
	/// </summary>
	/// <param name="game"></param>
	virtual bool updateObject(GAME* game);
 
};

#endif