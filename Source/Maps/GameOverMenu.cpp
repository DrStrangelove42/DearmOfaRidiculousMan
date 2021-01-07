#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(Player& p, GAME* g) : Menu(p, g)
{
	RenderContext& r = *(g->renderer);
	addButton(new Button("RETRY", r, SZ_SCREENWIDTH / 3, 2 * SZ_SCREENHEIGHT / 3, 0, [this](int i) {onRetryClick(i); }, 0x00aa00ff, 0x00ff00ff));
	addButton(new Button("QUIT", r, 2 * SZ_SCREENWIDTH / 3, 2 * SZ_SCREENHEIGHT / 3, 0, [this](int i) {onQuitClick(i); }, 0xaaaaaaff, 0xaaaaffff));

	addLabel(new Label("GAME OVER !", r, SZ_SCREENWIDTH / 2 - 50, SZ_SCREENHEIGHT / 2, 0xaa00aaff));
	
}

void GameOverMenu::onRetryClick(int id)
{
	game->player->reset(3);
	changeMap(game, "Main menu", 0, 0);//déjà chargée
}

void GameOverMenu::onQuitClick(int id)
{
	game->quit = true;
}

void GameOverMenu::onKeyDown(GAME* game)
{
	switch (game->keyLetter)
	{
	case 'Q':
		onQuitClick(0);
		break;
	case 'R':
		onRetryClick(0);
		break;

	default:
		break;
	}
}
