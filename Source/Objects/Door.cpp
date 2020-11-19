#include "Door.h"

Door::~Door()
{

}

Door::Door(string identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(identifier, posx, posy, p, "door"+identifier.substr(4,1), renderer, false)
{

}

void Door::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
        if (ea==NULL || traversable || abs(x-p.getX())+abs(y-p.getY())>1)
        {
	        return;
        }
        if (p.hasItem("k"+id.substr(3,1)))
        {
                traversable = true;
		texture = "door"+id.substr(5,1);
		updateTexture(renderer);
        } 
}
