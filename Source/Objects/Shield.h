#ifndef SHIELD_H
#define SHIELD_H

#include "Object.h"

using namespace std;

//Identifier starts with sh

class Shield : public Object
{
public:
	/* Destructor. */
	~Shield();

	/// <summary>
	/// Initialises a new Shield with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="defense"></param>
	Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense = 10);

	/// <summary>
	/// Function that updates a shield present in the Room.
	/// </summary>
	/// <param name="game"></param>
	void updateObject(GAME* game);
};

#endif
