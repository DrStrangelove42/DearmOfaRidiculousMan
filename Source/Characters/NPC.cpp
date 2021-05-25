#include "NPC.h"

#include "../Maps/Map.h"

void NPC::setTexture(RenderContext& renderer)
{
	text = renderer.LoadText(GetText(name) + " :\n" + GetText(speech), 0xD6C3C2FF, 0x000000FF, SZ_INFOSWIDTH - 10);
}

NPC::NPC(string id, string name, string speech, int posx, int posy, string tx, RenderContext& renderer, Map* map, bool trav) :
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
	if (isPlayerNearby(game->player))
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



		RenderContext& r = *(game->renderer);
		text->renderUnscaled(r, SZ_MAINWIDTH + 5, SZ_SCREENHEIGHT / 2);
		for (Button* btn : choices)
			btn->render(r);


		for (Button* btn : choices)
			btn->tick(0, game); //No need for time in a button
	}
	else //player out of reach
	{
		if (signedInForEvents)//remove buttons handlers
		{
			container = game->currentMap;
			for (Button* btn : choices)
				game->currentMap->removeMouseHandler(btn);
			signedInForEvents = false;
		}
	}
	return false;
}


void NPC::addChoice(string caption, RenderContext& r, function<void(int)> callback)
{
	choices.push_back(new Button(caption, r, SZ_MAINWIDTH + 2 * SZ_BLOCKSIZE, SZ_BLOCKSIZE + SZ_SCREENHEIGHT / 2 + text->getHeight() + int(choices.size()) * SZ_BLOCKSIZE * 3, int(choices.size()), callback, 0xD6C3C2FF, 0x8DBCE8FF));
}

void NPC::addChoice(Button* button)
{
	button->teleport(SZ_MAINWIDTH + 2 * SZ_BLOCKSIZE, SZ_BLOCKSIZE + SZ_SCREENHEIGHT / 2 + text->getHeight() + int(choices.size()) * SZ_BLOCKSIZE * 3);
	choices.push_back(button);
}

string NPC::objectToString()
{
	return id + " " + name + " " + speech;
}
