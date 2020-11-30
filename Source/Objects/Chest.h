#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "../Items/Item.h"
#include "../Items/Sword.h"
#include "../Items/Shield.h"
#include <unordered_map>

class Chest : public Object
{
private:
	/// <summary>
	/// An array of items contained in the chest. 
	/// </summary>
	unordered_map<Item, int, ItemHash> contents;
public:
	/*Destructor*/
	~Chest();

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Chest(string identifier, int posx, int posy, RenderContext& renderer);
	
	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="uniqueId"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Chest(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer);
	
	/// <summary>
	/// Returns a reference to the array of items that are in the chest.
	/// </summary>
	/// <returns></returns>
	unordered_map<Item, int, ItemHash>& getContents();

	/// <summary>
	/// Adds count times the item i to the chest.
	/// </summary>
	/// <param name="i"></param>
	/// <param name="count"></param>
	void addItem(Item i, int count = 1);

	/// <summary>
	/// How does a chest interact with the player?
	/// </summary>
	/// <param name="game"></param>
	void updateObject(GAME* game);
};

#endif
