#ifndef BLOCK_H
#define BLOCK_H

#include "../Base/Entity.h"

class Block : public Entity
{
protected:
	 //Position of the block
	 int x, y;
	 //Player
	 Player* player;
	 //The texture
	 string texture;

public:
	 Block(int posx, int posy, Player* player, string text);
	 int getX();
	 int getY();
};

#endif
