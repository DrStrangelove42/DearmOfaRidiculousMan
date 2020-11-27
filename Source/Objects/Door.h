#ifndef DOOR_H
#define DOOR_H

#include "Object.h"

class Door : public Object
{
public:
	/*Destructor*/
	~Door();
	
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	Door(string identifier, int posx, int posy, Player& p, RenderContext& renderer);

	/// <summary>
	///  How does a door interact with the player?
	/// </summary>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="ea"></param>
	void updateObject(Player& p, GAME* game);
};

#endif
