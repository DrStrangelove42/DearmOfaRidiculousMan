/* Entry point */

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

int main(int argc, char ** argv)
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


}
