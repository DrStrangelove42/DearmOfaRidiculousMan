#include "Chest.h"

Chest::~Chest()
{

}

Chest::Chest(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "closedchest", renderer, false)
{

}

Chest::Chest(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer) : Chest(headerline.substr(0, 2), posx, posy, renderer)
{
	headerline.erase(0, 3);
	// After the identifier, the items in the chest are described between parentheses, one after the other.
	while (headerline.length() > 0 && headerline[0] == '(')
	{
		size_t nextpar = headerline.find(')');
		string currentItem = headerline.substr(1, nextpar - 1);
		headerline.erase(0, nextpar + 2);
		if (currentItem.substr(0, 2) == "sw")
		{
			currentItem.erase(0, 3);
			try
			{
				int attack = stoi(currentItem);
				addItem(Sword("sw" + to_string(*(uniqueId)++), renderer, attack));
			}
			catch (...)
			{
				addItem(Sword("sw" + to_string(*(uniqueId)++), renderer));
			}
		}
		else if (currentItem.substr(0, 2) == "sh")
		{
			currentItem.erase(0, 3);
			try
			{
				int defense = stoi(currentItem);
				addItem(Shield("sh" + to_string(*(uniqueId)++), renderer, defense));
			}
			catch (...)
			{
				addItem(Shield("sh" + to_string(*(uniqueId)++), renderer));
			}
		}
	}
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

void Chest::updateObject(GAME* game)
{
	if (texture == "openchest" || abs(x - game->player->getX()) + abs(y - game->player->getY()) > 1)
	{
		return;
	}
	texture = "openchest";
	RenderContext& renderer = *(game->renderer);
	updateTexture(renderer);
	for (auto& entry : contents)
	{
		game->player->pickUpItem(entry.first, entry.second);

		//The following part might need to be changed if the player skins become more complex, but its purpose is to change the skin of the player if a shield or sword is found in a chest

		string itemid = entry.first.getId();
		if ((game->player->textureId == "player" || game->player->textureId == "playershield") && itemid.length() >= 2 && itemid.substr(0, 2) == "sw")
		{
			game->player->textureId += "sword";
		}
		if ((game->player->textureId == "player" || game->player->textureId == "playersword") && itemid.length() >= 2 && itemid.substr(0, 2) == "sh")
		{
			game->player->textureId += "shield";
		}
		game->player->updateTexture(renderer);
	}


}
