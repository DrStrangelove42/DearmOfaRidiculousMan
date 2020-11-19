#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

using namespace std;

//Identifier starts with sh

class Shield : public Entity
{
public:
	/* Destructor. */
	~Shield();

	/* Initialises a new Item with the specified informations. */
	Shield(string identifier, RenderContext& renderer, int defense=10);
};

#endif
