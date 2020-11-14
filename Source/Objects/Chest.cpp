#include "Chest.h"

Chest::~Chest()
{
	delete[] contents;
}

Chest::Chest(unordered_map<Item, int> contents, string identifier, int posx, int posy, Player& p, RenderContext& renderer) : 
  Object(identifier, posx, posy, p, "key", renderer, false), contents(contents)
{

}

unordered_map<Item, int> Chest::getContents()
{
	return contents;
}

void Chest::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{

}
