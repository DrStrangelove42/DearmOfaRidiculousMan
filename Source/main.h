#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include "Base/rendering.h"
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

typedef struct
{
	SDL_Window* window;
	RenderContext* renderer;
	Map* currentMap;
	bool quit;
} GAME;

/* Go to the main rendering loop of the game */
int playDoarm(GAME* game);

/* Events */
void manageEvents(GAME* game);
void onKeyDown(SDL_Event event);
void onWindowEvent(SDL_Event, GAME*);
GAME* initGame();
void quitGame(GAME* game);



#endif