#include "Chest.h"

Chest::~Chest()
{
  delete[] contents;
}

Chest::Chest(Item* contents, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "key", renderer), contents(contents)
{

}

char Chest::getContents()
{
	return contents;
}

void Chest::updateObject(Player& p, RenderContext& renderer){
  
}
