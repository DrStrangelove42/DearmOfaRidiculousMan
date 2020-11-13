#include "Warp.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, Player& p, RenderContext& renderer) :
	Object(posx, posy, p, "empty", renderer), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY)
{

}

void Warp::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
	if (destMap == currentMap)
	{
		*(ea->currentRoom) = destRoom;
		p.teleport(destX, destY);
	}
	{
		//TODO not sure how this would work with events, etc
		//ea->warp_IsExternal=true;
		//Load "WorldName".append(destMap);
		currentRoom = destRoom;
		p.teleport(destX, destY);
	}
}
