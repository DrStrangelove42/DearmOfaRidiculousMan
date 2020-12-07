#ifndef SWORD_H
#define SWORD_H

#include "Object.h"

using namespace std;

// The id of a sword starts with sw. //

class Sword : public Object
{
public:
	/* Destructor. */
	~Sword();

	/// <summary>
	/// Initialises a new Sword with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="attack"></param>
	Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack = 10);

	/// <summary>
	/// Function that updates a sword present in the Room.
	/// </summary>
	/// <param name="game"></param>
	void updateObject(GAME* game);
};

#endif
