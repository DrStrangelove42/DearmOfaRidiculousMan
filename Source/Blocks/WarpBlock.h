#ifndef WARPBLOCK_H
#define WARPBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"

class WarpBlock : public Block
{
public:
	/* This method is called when the player enters the block. */
	virtual void onEnter(EVENT_ARGS* ea);
};

#endif
