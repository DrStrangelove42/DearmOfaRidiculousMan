#include "Warp.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, string worldname, string ext, Player& p, RenderContext& renderer) :
  Object(identifier, posx, posy, p, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), worldname(worldname), ext(ext)
{

}

void Warp::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
        if (destMap == *(ea->currentMap))
	{
		*(ea->currentRoom) = destRoom;
		p.teleport(destX, destY);
	}
	else
	{
	          *(ea -> currentMap)=destMap;
		  *(ea -> currentRoom)=destRoom;
		  mapFromFiles(worldname, ext, p, renderer, destMap, destRoom, destX, destY);
	}
}
