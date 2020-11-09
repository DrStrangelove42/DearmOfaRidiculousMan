#include "WarpBlock.h"

WarpBlock::WarpBlock(int posx, int posy, Player& p, string tx, RenderContext& renderer, int warpTo, int toX, int toY) : Block(posx, posy, p, tx, renderer)
{
	toRoom = warpTo;
	destX = toX;
	destY = toY;
}

void WarpBlock::onEnter(EVENT_ARGS* ea)
{
	*(ea->currentRoom) = toRoom;
	player.teleport(destX, destY);
}

/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
void WarpBlock::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int X = (x + offsetX) * SZ_BLOCKSIZE;
	int Y = (y + offsetY) * SZ_BLOCKSIZE;
	Block::render(renderer, offsetX, offsetY);
	/*DEBUG*/
	renderer.changeColor(0x0088ffff);
	renderer.drawRectangle(X, Y, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	renderer.drawLine(X, Y, X + SZ_BLOCKSIZE, Y + SZ_BLOCKSIZE);
	renderer.drawLine(X+ SZ_BLOCKSIZE, Y, X , Y + SZ_BLOCKSIZE);

}