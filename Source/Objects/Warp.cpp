#include "Warp.h"
#include "../Maps/Map.h"
#include "../Maps/MainMenu.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay) :
	Object(identifier, posx, posy, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay)
{

}

Warp::Warp(string information, int* uniqueId, int posx, int posy, RenderContext& renderer) : Object(information.substr(0,2)+to_string((*uniqueId)++), posx, posy, "empty", renderer, true)
{
        size_t a;
        information.erase(0, 3);
	destMap = stoi(information, &a);
	information.erase(0, a+1);
	destRoom = stoi(information, &a);
	information.erase(0, a+1);
	destX = stoi(information, &a);
	information.erase(0, a+1);
	destY = stoi(information, &a);
	information.erase(0, a);
	try
	{
	        delay = stoi(information);
	}
	catch(...)
	{
	        delay = 0;
	}
}

void Warp::updateObject(GAME* game)
{
	if (delay > 0)
	{
		delay--;
		return;
	}
	if (x != game->player->getX() || y != game->player->getY())
	{
		return;
	}

	RenderContext& renderer = *(game->renderer);
	game->player->teleport(destX, destY);
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
		game->currentMap = new Map(game->worldName, *(game->player), renderer, game->currentMapId, destRoom);
	}

	else
		game->currentMap->getRooms()[destRoom]->setDiscovered(true);
}
