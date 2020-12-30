#include "Signboard.h"
#include "../Characters/Player.h"

void Signboard::setTexture(string text, RenderContext& renderer)
{
	textContent = renderer.LoadText(text, 0x724A0EFF, 0xF4C886FF, SZ_INFOSWIDTH - 10, 10);
}

Signboard::~Signboard()
{
}

Signboard::Signboard(string identifier, int posx, int posy, RenderContext& renderer, string content) :
	Object(identifier, posx, posy, "signboard", renderer, true), textContent(NULL)
{
	if (!content.empty())
		setTexture(content, renderer);
}



Signboard::Signboard(string headerline, int posx, int posy, RenderContext& renderer) :
	Signboard(EatToken(headerline), posx, posy, renderer, "")
{
	setTexture(GetText(headerline), renderer);
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


