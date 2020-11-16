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
#include "Base/events.h"
#include "Maps/Room.h"
#include "Maps/Map.h"
#include "Characters/Player.h"
#include "MapCreation/mapFromFile.h"

using namespace std;

/* Go to the main rendering loop of the game */
int playDoarm(GAME* game);

/* Initializes the GAME structure. */
GAME* initGame();





#endif
