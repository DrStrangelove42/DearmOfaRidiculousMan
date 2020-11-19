#ifndef ITEM_H
#define ITEM_H

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include <string>

using namespace std;

/*The word Item describes anything that is collectable by a player. 
Not to be confused with Objects. Items cannot be present on the map. 
An Object that is picked up by the player becomes an Item.*/
// todo: add a limit property and current number property of items
class Item : public Entity
{
protected:
        /* Identifier of the item */
        string id;
	/* The texture ID */
	string texture;
	/* The loaded texture */
	Texture* loadedTx;
	/* Attack characteristic, makes the player's attacks stronger. */
        int attack;
	/* Defense characteristic, makes the player's defense stronger. */
	int defense;

public:
	/* Destructor. */
	~Item();

	/* Initialises a new Item with the specified informations. */
	Item(string identifier, string tx, RenderContext& renderer, int attack, int defense);

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/* The following function describes how each type of item interacts withthe map when the player uses it.*/
	virtual void useItem();

	/* Time management */
	virtual void tick(int time, RenderContext& r);

	/* Forces the item to reload the texture corresponding to the current ID in <texture>.
	Note that there is no function to change the texture from the outside of the object, because we
	don't want to, for now.*/
	virtual void updateTexture(RenderContext& renderer);

	/* Getter */
	string getId() const;

	bool operator== (const Item& otherItem) const
	{
		return otherItem.id == id;
	}
	
	//virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
};

struct ItemHash
{
	size_t operator()(const Item& i) const
	{
		return hash<string>()(i.getId());
	}
};

#endif
