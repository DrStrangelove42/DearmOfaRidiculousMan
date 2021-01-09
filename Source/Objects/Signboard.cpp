#include "Signboard.h"
#include "../Characters/Player.h"

void Signboard::setTexture(RenderContext& renderer)
{
	textContent = renderer.LoadText(GetText(text), 0x724A0EFF, 0xF4C886FF, SZ_INFOSWIDTH - 10, 10);
}

Signboard::~Signboard()
{
}

Signboard::Signboard(string identifier, int posx, int posy, RenderContext& renderer, string content) :
	Object(identifier, posx, posy, "signboard", renderer, true), textContent(NULL), text(content)
{
	if (!text.empty())
		setTexture(renderer);
}



Signboard::Signboard(string headerline, int posx, int posy, RenderContext& renderer) :
	Signboard(EatToken(headerline), posx, posy, renderer, "")
{
	text = headerline;
	setTexture(renderer);
}

bool Signboard::updateObject(GAME* game)
{
	if (abs(x - game->player->getX()) < 2 &&
		abs(y - game->player->getY()) < 2)
	{
		textContent->renderUnscaled(*(game->renderer), SZ_MAINWIDTH + 5, SZ_SCREENHEIGHT / 2);
	}

	return false;
}

string Signboard::objectToString() const
{
	return id + " " + text;
}
