#ifndef BLOCK_H
#define BLOCK_H

#include "../Base/Entity.h"

class Block : public Entity
{
protected:
	 //Position of the block
	 int abs, ord;
	 //Player
	 Player* player;
	 //The texture
	 string texture;
public:
	 Block(int x, int y, Player* player, string text);
	 int getX();
	 int getY();
};

#endif
