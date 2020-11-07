/* Entry point */

#include "main.h"

using namespace std;

int main(int argc, char** argv)
{
	int status = 0;

	if (!renderInit())
		return DumpError("Init error.");
	
	GAME* game = initGame();

	if (NULL == game)
		return EXIT_FAILURE;

	status = playDoarm(game);

	/*Free the memory*/
	FreeTextures();
	
	quitGame(game);
	return status;
}

/*Main loop*/
int playDoarm(GAME* game)
{
	RenderContext& renderer = *(game->renderer);
	Player me(renderer);

	game->currentMap = new DummyMap(me, renderer); //POC

	while (!(game->quit))
	{
		game->renderer->clear();
		
		manageEvents(game);

		game->currentMap->render(renderer);

		me.render(renderer);

		game->renderer->update();

		renderSleep(50);
	}

	return EXIT_SUCCESS;
}

GAME* initGame()
{
	InitUtils();

	GAME* game = new GAME();

	game->quit = false;
	game->window = renderCreateWindow();

	if (NULL == game->window)
	{
		DumpError("Window error.");
		return NULL;
	}

	game->renderer = new RenderContext(game->window);

	return game;
}

void quitGame(GAME* game)
{
	delete game->currentMap;
	delete game->renderer;

	SDL_DestroyWindow(game->window);
}

void manageEvents(GAME * game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;

		case SDL_WINDOWEVENT:
			onWindowEvent(event, game);
			break;

		default:
			break;
		}
	}
}

void onWindowEvent(SDL_Event event, GAME * game)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		game->quit = true;
}

void onKeyDown(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_DOWN:
		break;
	case SDLK_UP:
		break;
	case SDLK_LEFT:
		break;
	case SDLK_RIGHT:
		break;
	default:
		break;
	}
}

