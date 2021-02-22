#include "Coin.h"
#include "../Characters/Player.h"

Coin::Coin(string identifier, int posx, int posy, RenderContext& renderer, int money) :
	Object(identifier, posx, posy, "*coin", renderer, true, to_string(money) + " gold"), money(money)
{
	((AnimatedTexture*)loadedTx)->setDelay(100);
}

Coin::Coin(string headerLine, int posx, int posy, RenderContext& renderer)
	: Coin(headerLine, posx, posy, renderer, stoi(headerLine.substr(1)))
{

}

bool Coin::updateObject(GAME* game)
{
	if (x != game->player->getX() || y != game->player->getY())
	{
		return false;
	}

	game->player->addMoney(money);

	/*Delete the pointer from the room*/
	return true;
}

string Coin::objectToString() const
{
	return "coin " + to_string(money);
}
