#include "NPC.h"
#include "Player.h"
#include "../Maps/Map.h"

void NPC::setTexture(RenderContext& renderer)
{
	text = renderer.LoadText(GetText(name) + " :\n" + GetText(speech), 0xD6C3C2FF, SZ_INFOSWIDTH - 10);
}

NPC::NPC(string id,string name, string speech, int posx, int posy, string tx, RenderContext& renderer, Map* map, bool trav) :
	Object(id, posx, posy, tx, renderer, trav), speech(speech), signedInForEvents(false), container(map), name(name)
{
	setTexture(renderer);
}

NPC::~NPC()
{
	for (Button* b : choices)
	{
		if (container != NULL)
			container->removeMouseHandler(b);
		delete b;
	}
	choices.clear();
}

bool NPC::updateObject(GAME* game)
{
	if (!signedInForEvents)
	{
		container = game->currentMap;
		for (Button* btn : choices)
			game->currentMap->addMouseHandler(btn,
				[btn](MOUSE_DATA* md)
				{
					btn->onMouseEvent(md);
				}
		);
		signedInForEvents = true;
	}


	if (abs(x - game->player->getX()) < 2 &&
		abs(y - game->player->getY()) < 2)
	{
		RenderContext& r = *(game->renderer);
		text->renderUnscaled(r, SZ_MAINWIDTH + 5, SZ_SCREENHEIGHT / 2);
		for (Button* btn : choices)
			btn->render(r);
	}

	for (Button* btn : choices)
		btn->tick(0, game); //No need for time in a button

	return false;
}

void NPC::addChoice(string caption, RenderContext& r, function<void(int)> callback)
{
	choices.push_back(new Button(caption, r, SZ_MAINWIDTH + 2 * SZ_BLOCKSIZE, SZ_BLOCKSIZE + SZ_SCREENHEIGHT / 2 + text->getHeight() + int(choices.size()) * SZ_BLOCKSIZE * 3, int(choices.size()), callback, 0xD6C3C2FF, 0x8DBCE8FF));
}

string NPC::objectToString()
{
	return id + " " + name + " " + speech;
}
