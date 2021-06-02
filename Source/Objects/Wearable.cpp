#include "Wearable.h"

Wearable::~Wearable()
{

}
 
Wearable::Wearable(string identifier, int posx, int posy, string tx, RenderContext& renderer) :
	PickableObject(identifier, posx, posy, tx, renderer)
{

}

