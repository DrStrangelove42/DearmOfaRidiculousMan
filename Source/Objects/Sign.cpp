#include "Sign.h"
#include "../Characters/Player.h"

void Sign::setTexture(RenderContext& renderer)
{
	textContent = renderer.LoadText(GetText(text), 0x724A0EFF, 0xF4C886FF, SZ_INFOSWIDTH - 10, 10);
}

Sign::~Sign()
{
}

Sign::Sign(string identifier, int posx, int posy, RenderContext& renderer, string content) :
	Object(identifier, posx, posy, "sign", renderer, true), textContent(NULL), text(content)
{
	if (!text.empty())
		setTexture(renderer);
}



Sign::Sign(string headerline, int posx, int posy, RenderContext& renderer) :
	Sign(EatToken(headerline), posx, posy, renderer, "")
{
	text = headerline;
	setTexture(renderer);
}

bool Sign::updateObject(GAME* game)
{
	if (abs(x - game->player->getX()) < 2 &&
		abs(y - game->player->getY()) < 2)
	{
		textContent->renderUnscaled(*(game->renderer), SZ_MAINWIDTH + 5, SZ_SCREENHEIGHT / 2);
	}

	return false;
}

string Sign::objectToString() const
{
	return id + " " + text;
}
