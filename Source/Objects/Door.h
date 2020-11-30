#ifndef DOOR_H
#define DOOR_H

#include "Object.h"

class Door : public Object
{
private:
  	/// <summary>
	/// Identifier of the key that unlocks this door. It is a string of length 1, and the door is unlocked by the key having identifier "k" + keyId.
	/// </summary>
	string keyId;

	/// <summary>
	/// Orientation of the door when it is open, it is a string of length 1 equal to "n", "e", "s", or "w", which also tells us which texture to use when the door is open ("door" + openOrientation)
	/// </summary>
	string openOrientation;


	/// <summary>
	/// Orientation of the door when it is closed, it is a string of length 1 equal to "n", "e", "s", or "w", which also tells us which texture to use when the door is closed ("door" + closedOrientation)
	/// </summary>
	string closedOrientation;
public:
	/*Destructor*/
	~Door();
	
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="KeyId"></param>
	/// <param name="openOrientation"></param>
	/// <param name="closedOrientation"></param>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Door(string keyId, string openOrientation, string closedOrientation, string identifier, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Door(string headerline, int posx, int posy, RenderContext& renderer);

	/// <summary>
	///  How does a door interact with the player?
	/// </summary>
	/// <param name="game"></param>
	void updateObject(GAME* game);
};

#endif
