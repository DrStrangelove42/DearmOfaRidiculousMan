#include "NPC.h"
#include "Player.h"

void NPC::setTexture(RenderContext& renderer)
{
	text = renderer.LoadText(GetText(id) + " :\n" + GetText(speech), 0xD6C3C2FF, SZ_INFOSWIDTH - 10);
}

NPC::NPC(string name, string speech, int posx, int posy, string tx, RenderContext& renderer, bool trav) :
	Object(name, posx, posy, tx, renderer, trav), speech(speech)
{
	setTexture(renderer);
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

void NPC::addChoice(string caption, RenderContext& r, function<void(int)> callback)
{
	choices.push_back(new Button(caption, r, 5, text->getHeight() + int(choices.size()) * RenderContext::FONTSIZE * 3, int(choices.size()), callback));
}