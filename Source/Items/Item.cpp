#include "Item.h"

Item::Item(string identifier, string tx, RenderContext& renderer, int attack, int defense) : id(identifier), texture(tx), attack(attack), defense(defense)
{
	updateTexture(renderer);
}

Item::~Item()
{

}

void Item::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}

void Item::useItem()
{

}

void Item::render(RenderContext& renderer, int offsetX , int offsetY )
{
	//Do not render anything as an Item is abstract for us.
}

void Item::tick(int time, RenderContext& r)
{

}

int Item::getAttack()
{
	return attack;
}

int Item::getDefense()
{
	return defense;
}

string Item::getId() const
{
        return id;
}
