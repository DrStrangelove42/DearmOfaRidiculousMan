#ifndef BLOCK_H
#define BLOCK_H

#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"
#include "../Base/game.h"

class Block : public DrawableEntity
{
protected:
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
	/// <param name="tx">Texture ID</param>
	/// <param name="renderer"></param>
	/// <param name="trav">If the block is traversable</param>
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

	/// <summary>
	/// Places the moving entity on this block.
	/// </summary>
	/// <param name="m"></param>
	void teleportOn(MovingEntity& m);

	/* Time management */
	virtual void tick(int time, GAME* game);

	
};

#endif
