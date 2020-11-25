#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "../Items/Item.h"
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

	/*Constructor*/
	Chest(string identifier, int posx, int posy, Player& p, RenderContext& renderer);
	
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
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="ea"></param>
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
};

#endif
