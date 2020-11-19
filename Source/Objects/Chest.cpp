#include "Chest.h"

Chest::~Chest()
{
	
}

Chest::Chest(string identifier, int posx, int posy, Player& p, RenderContext& renderer) :
	Object(identifier, posx, posy, p, "closedchest", renderer, false)
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
		contents[i] += count;
}

void Chest::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
        if (ea == NULL || texture == "openchest" || abs(x - p.getX()) + abs(y - p.getY())>1)
	{
	        return;
	}
	texture = "openchest";
	updateTexture(renderer);
	for (auto& entry : contents)
	{
	        p.pickUpItem(entry.first, entry.second);

		//The following part might need to be changed if the player skins become more complex, but its purpose is to change the skin of the player if a shield or sword is found in a chest
		
		string itemid = entry.first.getId();
		if ((p.texture == "player" || p.texture == "playershield") && itemid.length() >= 2 && itemid.substr(0,2) == "sw")
		{
		        p.texture+="sword";
		}
		if ((p.texture == "player" || p.texture == "playersword") && itemid.length() >= 2 && itemid.substr(0,2) == "sh")
		{
		        p.texture+="shield";
		}
		p.updateTexture(renderer);
	}
	
  
}
