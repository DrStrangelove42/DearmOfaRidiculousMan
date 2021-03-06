#include "Chest.h"
#include "../Characters/Player.h"

Chest::~Chest()
{
	list<const PickableObject*> toDel;
	for (auto& e : contents)
	{
		toDel.push_back(e.first);
	}
	contents.clear();
	for (const PickableObject* p : toDel)
		delete p;
}

Chest::Chest(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "closedchest", renderer, false)
{

}

Chest::Chest(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer) : Chest("", posx, posy, renderer)
{
	size_t pos = headerline.find(" ");
	id = headerline.substr(0, pos);
	headerline.erase(0, pos + 1);
	// After the identifier, the items in the chest are described between parentheses, one after the other.
	while (headerline.length() > 0 && headerline[0] == '(')
	{
		size_t nextpar = headerline.find(')');
		string currentObject = headerline.substr(1, nextpar - 1);
		headerline.erase(0, nextpar + 2);

		PickableObject* obj = (PickableObject*)Map::parseObject(currentObject, renderer, uniqueId, -1, -1);
		try
		{
			size_t a;
			int count = stoi(headerline, &a);
			headerline.erase(0, a + 1);
			addObject(obj, count);
		}
		catch (...)
		{
			addObject(obj);
		}
	}
}

unordered_map<PickableObject*, int>& Chest::getContents()
{
	return contents;
}

void Chest::addObject(PickableObject* obj, int count)
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
	}

	contents.clear();

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
