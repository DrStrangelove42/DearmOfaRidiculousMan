/* Entry point */

#include "main.h"

using namespace std;

int main(int argc, char** argv)
{
	int status = 0;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return DumpError("Init error.");

	if (SDL_CreateWindowAndRenderer(
		SZ_SCREENWIDTH,
		SZ_SCREENHEIGHT,
		SDL_WINDOW_SHOWN,
		&window,
		&renderer) != 0)
		return DumpError("Window error.");
	
	InitGame();

	status = playDoarm(window, renderer);

	/*Free the memory*/
	FreeTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return status;
}

/*Main loop*/
int playDoarm(SDL_Window* window, SDL_Renderer* renderer)
{
	Player me(renderer);
	DummyMap currentMap(me, renderer); //POC
	bool quit = false; 

	while (!quit)
	{
		SDL_RenderClear(renderer);
		
		manageEvents(&quit);

		currentMap.render(renderer);

		me.render(renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(50);
	}

	return EXIT_SUCCESS;
}

void manageEvents(bool * quit)
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
			onWindowEvent(event, quit);
			break;

		default:
			break;
		}
	}
}

void onWindowEvent(SDL_Event event, bool * quit)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		*quit = true;
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
