#ifndef BLOCK_H
#define BLOCK_H

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
class Block : public Entity
{
protected:
	//Position of the block
	int x, y;
	//Player
	Player& player;
	//The texture
	string texture;
	SDL_Texture* loadedTx;

public:
	~Block();
	Block(Player& player);
	Block(int posx, int posy, Player& player, string tx, SDL_Renderer* renderer);
	int getX();
	int getY();
	void move(int px, int py);
	void render(SDL_Renderer* renderer);
	void teleportOn(MovingEntity& m);
	virtual void tick(int time);
};

#endif
