/* Entry point */

#include "main.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 
#include <time.h>
#include "Base/config.h"
#include "Maps/Map.h"


using namespace std;

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer(
		SZ_SCREENWIDTH,
		SZ_SCREENHEIGHT,
		SDL_WINDOW_SHOWN,
		&window,
		&renderer);

	playDoarm(window, renderer);

	/*Free the memory*/
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

/*Main loop*/
int playDoarm(SDL_Window* window, SDL_Renderer* renderer)
{
	Map currentMap;
	bool quit = false;


	while (!quit)
	{
		SDL_RenderClear(renderer);
		
		manageEvents();

		SDL_RenderCopy(renderer, texturePerso, NULL, &persoPos);
		SDL_RenderPresent(renderer);

		SDL_Delay(50);
	}

}

void manageEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			Event_KeyDown()

			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				quit = true;
			break;
		default:
			break;
		}
	}
}

void Event_KeyDown()
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
