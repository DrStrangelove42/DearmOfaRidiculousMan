#ifndef BLOCK_H
#define BLOCK_H

#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"
#include "../Base/game.h"

/// <summary>
/// A Block is a DrawableEntity that is the main component of a Room. It is also the unit used for positioning <see cref="Entity">Entities within a Room.
/// </summary>
class Block : public DrawableEntity
{
protected:
	/// <summary>
	/// Indicates whether or not the Block can be occupied by a MovingEntity such as the Player.
	/// </summary>
	bool traversable;
public:
	/// <summary>
	/// Destructor.
	/// </summary>
	~Block();

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx">Texture ID</param>
	/// <param name="renderer"></param>
	/// <param name="trav">If the block is traversable</param>
	Block(int posx, int posy, string tx, RenderContext& renderer, bool trav = false);

	/// <summary>
	/// Get a Block's <see cref="Block::x">x</see> coordinate.
	/// </summary>
	int getX();
	
	/// <summary>
	/// Get a Block's <see cref="Block::y">y</see> coordinate.
	/// </summary>
	int getY();
	
	/// <summary>
	/// Get a Block's <see cref="Block::traversable">x</see> parameter.
	/// </summary>
	bool getTrav();

	/// <summary>
	/// Change the <see cref="Block::traversable">traversable</see> parameter of a Block.
	/// </summary>
	/// <param name="trav"></param>
	void setTrav(bool trav);

	/// <summary>
	/// Places the MovingEntity on this Block.
	/// </summary>
	/// <param name="m"></param>
	void teleportOn(MovingEntity& m);

	/// <summary>
	/// Time management.
	/// </summary>
	virtual void tick(int time, GAME* game);	
};

#endif
