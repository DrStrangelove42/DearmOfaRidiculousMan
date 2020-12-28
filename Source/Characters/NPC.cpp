#include "NPC.h"
#include "Player.h"

NPC::NPC(string name, string speech, int posx, int posy, string tx, RenderContext& renderer, bool trav) :
	Object(name, posx, posy, tx, renderer, trav), speech(speech)
{
	text = renderer.LoadText(id + " :\n" + speech, 0xD6C3C2FF, SZ_INFOSWIDTH - 10);
}

bool NPC::updateObject(GAME* game)
{
	if (abs(x - game->player->getX()) < 2 &&
		abs(y - game->player->getY()) < 2)
	{
		RenderContext& r = *(game->renderer);
		text->renderUnscaled(r, SZ_MAINWIDTH + 5, SZ_SCREENHEIGHT / 2);
		for (Button* btn : choices)
			btn->render(r);
	}

	return false;
}

void NPC::addChoice(string text, RenderContext& r, function<void(int)> callback)
{
	choices.push_back(new Button(text, r, 5, int(choices.size()) * RenderContext::FONTSIZE * 3,int(choices.size()), callback));
}