#include "Shop.h"

//#include "../Characters/Player.h"

Shop::Shop(string id, string name, string speech, int posx, int posy, RenderContext& renderer, Map* map) :
	NPC(id, name, speech, posx, posy, "shop", renderer, map, false), player(NULL)
{

}

Shop::~Shop()
{
	for (auto& entry : contents)
	{
		delete entry.first;
	}
	contents.clear();
}

Shop::Shop(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer) :
	Shop("", "", "", posx, posy, renderer, NULL)
{
	size_t pos = headerline.find(" ");
	id = headerline.substr(0, pos);
	headerline.erase(0, pos + 1);

	name = EatToken(headerline);
	speech = EatToken(headerline);
	setTexture(renderer);

	// After the identifier, the items in the chest are described between brackets [ and ] with count and price, one after the other.
	while (headerline.length() > 0 && headerline[0] == '[')
	{
		size_t nextpar = headerline.find('[', 1);
		string currentObject = headerline.substr(1, nextpar - 1);
		headerline.erase(0, nextpar);
		nextpar = currentObject.find(']');
		string objString = currentObject.substr(0, nextpar);
		currentObject.erase(0, nextpar + 1);
		PickableObject* obj = (PickableObject*)Map::parseObject(objString, renderer, uniqueId, -1, -1);

		size_t a;
		int count = stoi(currentObject, &a);
		currentObject.erase(0, a + 1);
		int price = stoi(currentObject);

		addObjectToSell(obj, count, price);
	}

	buildButtons(renderer);
}

bool Shop::updateObject(GAME* g)
{
	if (player == NULL)
		player = g->player;

	if (!isPlayerNearby(g->player))
	{
		g->currentMap->unregisterTopMostTexture("ShopBtnInfoTip");
	}

	return NPC::updateObject(g);
}


string Shop::objectToString() const
{
	string text = id;
	for (auto& entry : contents)
	{
		text += "[" + entry.first->objectToString() + "] " + to_string(entry.second.first) + " " + to_string(entry.second.second) + " ";
	}
	return text;
}



void Shop::buildButtons(RenderContext& r)
{
	int id = 0;
	for (auto& entry : contents)
	{
		//todo image+text
		Button* b = new InfoTipButton(
			r.LoadStringWithIcon("x" + to_string(entry.second.first) + " : " + to_string(entry.second.second) + " gold", entry.first->getTextureID(), 0xD39206FF),
			r,
			-1, -1 /*x and y will be set with addChoice()*/,
			id,
			[this, entry](int i)
			{
				if (player != NULL)
				{
					if (player->getMoney() >= entry.second.second)
					{
						//the player can buy the object
						player->addMoney(-entry.second.second);
						//Clone the object
						PickableObject* p = entry.first->clone();
						//Add the cloned object to the player
						player->pickUpObject(p, entry.second.first);
					}
				}
			},
			entry.first->getInfo()
		);
		addChoice(b);
		index.push_back(entry.first);
		id++;
	}
}

void Shop::addObjectToSell(PickableObject* pObj, int count, int price)
{
	contents[pObj] = { count,price };
}
