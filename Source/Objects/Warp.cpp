#include "Warp.h"

Warp::~Warp()
{

}

Warp::Warp(string destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, Player& p, RenderContext& renderer) :
	Object(identifier, posx, posy, p, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY)
{

}

void Warp::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
	if (destMap == ea->warp_MapToLoad)
	{
		*(ea->currentRoom) = destRoom;
		p.teleport(destX, destY);
	}
	{
		//TODO not sure how this would work with events, etc
		ea->warp_IsExternal=true;
		ea->warp_MapToLoad = destRoom;
		//p.teleport(destX, destY); <-- No, the new map handles this.
	}
}
