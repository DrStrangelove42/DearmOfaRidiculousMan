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

	quitGame(game);

	renderQuit();
	return status;
}

/*Main loop*/
int playDoarm(GAME* game)
{
	RenderContext& renderer = *(game->renderer);
	Player * me = new Player(renderer);

	game->player = me;

	string worldName = "NewTestMap";
	
	Map::worldFromFile(MAPFILES_LOCATION, worldName);
	worldName = MAPFILES_LOCATION + worldName + "/" + worldName;
	game->worldName = worldName;
	game->currentMapId = new int (-1);
	game->currentMap = new Map(worldName, *me, renderer, game->currentMapId);

	int currentTime;

	while (!(game->quit))
	{
		game->renderer->clear();

		manageEvents(game);

		game->currentMap->render(renderer);

		currentTime = GetTime();
		game->currentMap->tick(currentTime, renderer);
		game->player->tick(currentTime, renderer);

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

