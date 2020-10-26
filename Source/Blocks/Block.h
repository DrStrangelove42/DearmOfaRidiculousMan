#ifndef BLOCK_H
#define BLOCK_H

class Block : public Entity
{
protected:
	 //Position of the block
	 int abs, ord;
	 //Player
	 Player* player;
	 //File where the block's texture can be found
	 string texture;
public:
	 Block(int x, int y, Player* player, string text);
	 int getX();
	 int getY();
};

#endif
