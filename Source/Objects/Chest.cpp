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
		string currentObject = headerline.substr(1, nextpar - 1);
		headerline.erase(0, nextpar + 2);
		if (currentObject.substr(0, 2) == "sw")
		{
			currentObject.erase(0, 3);
			try
			{
				int attack = stoi(currentObject);
				addObject(Sword("sw" + to_string(*(uniqueId)++), -1, -1, renderer, attack));
			}
			catch (...)
			{
			  addObject(Sword("sw" + to_string(*(uniqueId)++), -1, -1, renderer));
			}
		}
		else if (currentObject.substr(0, 2) == "sh")
		{
			currentObject.erase(0, 3);
			try
			{
				int defense = stoi(currentObject);
				addObject(Shield("sh" + to_string(*(uniqueId)++), -1, -1, renderer, defense));
			}
			catch (...)
			{
			  addObject(Shield("sh" + to_string(*(uniqueId)++), -1, -1, renderer));
			}
		}
	}
}

unordered_map<Object, int, ObjectHash>& Chest::getContents()
{
	return contents;
}

void Chest::addObject(Object obj, int count)
{
	if (contents.find(obj) == contents.end())
		contents[obj] = count;
	else
		contents[obj] += count;
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
		game->player->pickUpObject(entry.first, entry.second);

		//The following part might need to be changed if the player skins become more complex, but its purpose is to change the skin of the player if a shield or sword is found in a chest

		string objid = entry.first.getId();
		if ((game->player->textureId == "player" || game->player->textureId == "playershield") && objid.length() >= 2 && objid.substr(0, 2) == "sw")
		{
			game->player->textureId += "sword";
		}
		if ((game->player->textureId == "player" || game->player->textureId == "playersword") && objid.length() >= 2 && objid.substr(0, 2) == "sh")
		{
			game->player->textureId += "shield";
		}
		game->player->updateTexture(renderer);
	}


}
