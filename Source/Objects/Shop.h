#ifndef SHOP_H
#define SHOP_H

#include "PickableObject.h"
#include "../Characters/NPC.h"
#include <unordered_map>
#include <vector>
#include "../Maps/Map.h"
#include "../Interactions/InfoTipButton.h"
 

/// <summary>
/// An Shop is an Entity that can be found in a Room, for the player to buys other objects
/// (deriving from PickableObject).
/// </summary>
class Shop : public NPC
{
protected:
	/// <summary>
	/// An array of items contained in the shop, and a pair (qty, price).
	/// </summary>
	unordered_map<PickableObject*, pair<int, int>> contents;

	/// <summary>
	/// Array of objects in the order of the buttons.
	/// </summary>
	vector<PickableObject*> index;

	Player* player;
public:
	virtual ~Shop();

	/// <summary>
	/// Initialises a new Shop with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	Shop(string id, string name, string speech, int posx, int posy, RenderContext& renderer, Map* map);

	/// <summary>
	/// Creates a shop based on a header line in a map file.
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="uniqueId"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Shop(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// Returns true if the object has been picked up (thus informing that we should remove it from the room)
	/// </summary>
	/// <param name="game"></param>
	virtual bool updateObject(GAME* game);

	/// <summary>
	/// Encodes the object into a string in the correct format (the same one used when creating maps, without the position)
	/// </summary>
	virtual string objectToString() const;

	/// <summary>
	/// Adds the buttons corresponding to the objects we can buy.
	/// </summary>
	void buildButtons(RenderContext& r);

	/// <summary>
	/// Adds an object in the choices. After you added all objects, call buildButtons to add the buttons in the window.
	/// </summary>
	/// <param name="pObj"></param>
	/// <param name="count"></param>
	/// <param name="price"></param>
	void addObjectToSell(PickableObject* pObj, int count, int price);
};

#endif
