#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "../Items/Item.h"
#include <unordered_map>

class Chest : public Object
{
private:
	/*An array of items contained in the chest.  */
	unordered_map<Item, int, ItemHash> contents;
public:
	/*Destructor*/
	~Chest();

	/*Constructor*/
	Chest(string identifier, int posx, int posy, Player& p, RenderContext& renderer);
	/* Returns a reference to the array of items that are in the chest. */
	unordered_map<Item, int, ItemHash>& getContents();

	/* Adds count times the item i to the chest. */

	void addItem(Item i, int count = 1);

	/* How does a chest interact with the player? */
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
};

#endif
