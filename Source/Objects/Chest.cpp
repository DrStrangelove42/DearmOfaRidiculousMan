#include "Chest.h"
#include "../Characters/Player.h"

Chest::~Chest()
{

}

Chest::Chest(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "closedchest", renderer, false)
{

}

Chest::Chest(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer) : Chest("", posx, posy, renderer)
{
	size_t pos = headerline.find(" ");
	id = headerline.substr(0,pos);
	headerline.erase(0,pos+1);
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
				addObject(new Sword("sw" + to_string(*(uniqueId)++), -1, -1, renderer, attack));
			}
			catch (...)
			{
				addObject(new Sword("sw" + to_string(*(uniqueId)++), -1, -1, renderer));
			}
		}
		else if (currentObject.substr(0, 2) == "sh")
		{
			currentObject.erase(0, 3);
			try
			{
				int defense = stoi(currentObject);
				addObject(new Shield("sh" + to_string(*(uniqueId)++), -1, -1, renderer, defense));
			}
			catch (...)
			{
				addObject(new Shield("sh" + to_string(*(uniqueId)++), -1, -1, renderer));
			}
		}
	}
}

unordered_map<Object*, int>& Chest::getContents()
{
	return contents;
}

void Chest::addObject(Object* obj, int count)
{
	if (contents.find(obj) == contents.end())
		contents[obj] = count;
	else
		contents[obj] += count;
}

bool Chest::updateObject(GAME* game)
{
	if (texture == "openchest" || abs(x - game->player->getX()) + abs(y - game->player->getY()) > 1)
	{
		return false;
	}
	texture = "openchest";
	RenderContext& renderer = *(game->renderer);
	updateTexture(renderer);
	for (auto& entry : contents)
	{
		game->player->pickUpObject(entry.first, entry.second);
		//The following part might need to be changed if the player skins become more complex, 
		//but its purpose is to change the skin of the player if a shield or sword is found in a chest

		string objid = entry.first->getId();
		string& refTexture = game->player->getTextureID();
		if ((refTexture == "player" || refTexture == "playershield") && objid.length() >= 2 && objid.substr(0, 2) == "sw")
		{
			refTexture += "sword";
		}
		if ((refTexture == "player" || refTexture == "playersword") && objid.length() >= 2 && objid.substr(0, 2) == "sh")
		{
			refTexture += "shield";
		}
		game->player->updateTexture(renderer);
	}

	return false;
}

string Chest::objectToString() const
{
	string encoding = id;
	if (texture != "openchest")
	{
		for (auto& entry : contents)
		{
			encoding += " (";
			encoding += entry.first->objectToString();
			encoding += ")";
		}
	}
	return encoding;	
}
