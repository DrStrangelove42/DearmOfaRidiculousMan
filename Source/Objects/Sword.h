#ifndef SWORD_H
#define SWORD_H

#include "PickableObject.h"

using namespace std;

// The id of a sword starts with sw. //

class Sword : public PickableObject
{
public: 

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
	/// We encode a sword with sw followed by the attack parameter.
	/// </summary>
	string objectToString() const;
};

#endif
