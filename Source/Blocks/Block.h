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

	/// <summary>
	/// The texture ID
	/// </summary>
	string texture;
	/// <summary>
	/// The loaded texture
	/// </summary>
	Texture* loadedTx;
	/// <summary>
	/// 
	/// </summary>
	bool traversable;
public:
	/* Destructor. */
	~Block();

	/// <summary>
	///  Initialises a new Block object with the specified informations. 
	/// </summary>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	Block(int posx, int posy, string tx, RenderContext& renderer, bool trav = false);

	/*Getters*/
	int getX();
	int getY();
	bool getTrav();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="trav"></param>
	void setTrav(bool trav);

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/// <summary>
	/// Places the moving entity on this block.
	/// </summary>
	/// <param name="m"></param>
	void teleportOn(MovingEntity& m);
	/// <summary>
	/// This method is called when the player enters the block. May end up being useless. 
	/// </summary>
	/// <param name="ea"></param>
	virtual void onEnter(EVENT_ARGS* ea);

	/* Time management */
	virtual void tick(int time, RenderContext&);

	/* Forces the object to reload the texture corresponding to the current ID in <texture>.
	Note that there is no function to change the texture from the outside of the object, because we
	don't want to, for now.*/
	virtual void updateTexture(RenderContext& renderer);
};

#endif
