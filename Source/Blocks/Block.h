#ifndef BLOCK_H
#define BLOCK_H

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
#include "../Maps/Room.h"

class Block : public Entity
{
protected:
	/* Position of the block */
	int x, y;
	/* Player */
	Player& player;
	/* The texture ID */
	string texture;
	/* The loaded texture */
	SDL_Texture* loadedTx;
	/* The room containing this block */
	Room& container;

public:
	/* Destructor. */
	~Block();

	/* Initialises a new Block object with the specified informations. */
	Block(int posx, int posy, Player& player, Room& room, string tx, SDL_Renderer* renderer);

	int getX();
	int getY();

	/* Change the block position. */
	void move(int px, int py);

	/* Rendering method. */
	void render(SDL_Renderer* renderer);

	/* Places the moving entity on this block. */
	void teleportOn(MovingEntity& m);

	/* Time management */
	virtual void tick(int time);
};

#endif
