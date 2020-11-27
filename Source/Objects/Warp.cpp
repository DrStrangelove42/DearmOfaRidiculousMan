#include "Warp.h"
#include "Warp.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, Player& p, RenderContext& renderer, int delay) :
  Object(identifier, posx, posy, p, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay)
{

}

void Warp::updateObject(Player& p, RenderContext& renderer, GAME* game)
{
        if (delay>0)
        {
                delay--;
		return;
	}
	if (x != p.getX() || y != p.getY())
	{
		return;
	}
	p.teleport(destX, destY);
	game->currentMap->currentRoom = destRoom;
	if (destMap == -1)
	{
	        *(game->currentMapId) = -1;
	        game->currentMap = new MainMenu(*(game->player), game);
		game->worldName = "Main menu";
		return;
	}
	if (destMap != *(game->currentMapId))
	{
		*(game->currentMapId) = destMap;
		game->currentMap = new Map(game->worldName, p, renderer, game->currentMapId, destRoom);
	}
	
	else
		game->currentMap->getRooms()[destRoom]->setDiscovered(true);
}
