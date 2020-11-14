#include "Chest.h"

Chest::~Chest()
{
	
}

Chest::Chest(string identifier, int posx, int posy, Player& p, RenderContext& renderer) :
	Object(identifier, posx, posy, p, "key", renderer, false)
{

}

unordered_map<Item, int, ItemHash>& Chest::getContents()
{
	return contents;
}

void Chest::addItem(Item i, int count)
{
	if (contents.find(i) == contents.end())
		contents[i] = count;
	else
		contents[i]++;
}

void Chest::updateObject(Player& p, RenderContext& renderer, 
	EVENT_ARGS* ea)
{

}
