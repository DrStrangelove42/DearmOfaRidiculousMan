#include "Warp.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, Player& p, RenderContext& renderer) :
	Object(identifier, posx, posy, p, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY)
{

}

void Warp::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
        if (ea==NULL || x!=p.getX() || y!=p.getY())
          {
            return;
          }
        p.teleport(destX, destY);
	*(ea->currentRoom) = destRoom;
	//cout << destMap << endl;
	//cout << *(ea->currentMap) << endl;

	if (destMap != *(ea->currentMap))
	{
	  //cout << "aa" << endl;
		*(ea->currentMap) = destMap;
		ea->warp_IsExternal = true;
	}
}
