#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

using namespace std;

//Identifier starts with sh

class Shield : public Item
{
public:
	/* Destructor. */
	~Shield();

	/// <summary>
	/// Initialises a new Item with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="renderer"></param>
	/// <param name="defense"></param>
	Shield(string identifier, RenderContext& renderer, int defense = 10);
};

#endif
