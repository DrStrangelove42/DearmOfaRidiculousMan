#ifndef SHOP_H
#define SHOP_H

#include "PickableObject.h"
#include <unordered_map>

/// <summary>
/// An Shop is an Entity that can be found in a Room, for the Player to interact with, in a Chest (which is an Shop in and of itself), for the Player to collect, or in a Player's inventory, for the Player to use.
/// </summary>
class Shop : public Object
{
protected:
	/// <summary>
	/// An array of items contained in the shop, and a pair (qty, price).
	/// </summary>
	unordered_map<PickableObject*, pair<int,int>> contents;
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
	Shop(string identifier, int posx, int posy, string tx, RenderContext& renderer);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// Returns true if the object has been picked up (thus informing that we should remove it from the room)
	/// </summary>
	/// <param name="game"></param>
	virtual bool updateObject(GAME* game);

	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="renderer"></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// Encodes the object into a string in the correct format (the same one used when creating maps, without the position)
	/// </summary>
	virtual string objectToString() const;

	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">blocks</see>) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">X Offset, in blocks.</param>
	/// <param name="offsetY">Y Offset, in blocks.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;
};

#endif
