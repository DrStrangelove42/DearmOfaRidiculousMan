#ifndef SWORD_H
#define SWORD_H

#include "Item.h"

using namespace std;

// The id of a sword starts with sw. //

class Sword : public Item
{
public:
	/* Destructor. */
	~Sword();

	/// <summary>
	/// Initialises a new Item with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="renderer"></param>
	/// <param name="attack"></param>
	Sword(string identifier, RenderContext& renderer, int attack = 10);
};

#endif
