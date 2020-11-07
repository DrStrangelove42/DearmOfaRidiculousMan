#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 
#include <time.h>
#include "Base/config.h"
#include "Base/utils.h"
#include "Maps/Room.h"
#include "Maps/Dummy.h"
#include "Maps/Map.h"
#include "Characters/Player.h"

/* Go to the main rendering loop of the game */
int playDoarm(SDL_Window* window, SDL_Renderer* renderer);

/* Events */
void manageEvents(bool* quit);
void onKeyDown(SDL_Event event);
void onWindowEvent(SDL_Event event, bool* quit);
GAME* initGame();

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Map* currentMap;
	bool quit;
} GAME;

#endif