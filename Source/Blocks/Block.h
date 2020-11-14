#ifndef BLOCK_H
#define BLOCK_H

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"

class Block : public Entity
{
protected:
	/* Position coordinates */
	int x;
	int y;
	/* Can we walk onto this block? */
	bool traversable;
	/* The texture ID */
	string texture;
	/* The loaded texture */
	Texture* loadedTx;

public:
	/* Destructor. */
	~Block();

	/* Initialises a new Block object with the specified informations. */
	Block(int posx, int posy, string tx, RenderContext& renderer, bool trav = false);

	/*Getters*/
	int getX();
	int getY();
	bool getTrav();

	void setTrav(bool trav);

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/* Places the moving entity on this block.*/
	void teleportOn(MovingEntity& m);

	/* This method is called when the player enters the block. May end up being useless. Vincent : Not sure : im using the traversable flag in onEnter,
	so I bring back this function from the dead.*/
	virtual void onEnter(EVENT_ARGS* ea);

	/* Time management */
	virtual void tick(int time);

	/* Forces the object to reload the texture corresponding to the current ID in <texture>.
	Note that there is no function to change the texture from the outside of the object, because we
	don't want to, for now.*/
	virtual void updateTexture(RenderContext& renderer);
};

#endif
