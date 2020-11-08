#ifndef WARPBLOCK_H
#define WARPBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"

class WarpBlock : public Block
{
	int toRoom;
	int destX;
	int destY;
public:
	WarpBlock(int posx, int posy, Player& p, string tx, RenderContext& renderer, int warpTo, int toX, int toY);

	/* This method is called when the player enters the block. */
	virtual void onEnter(EVENT_ARGS* ea);

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
};

#endif
