#ifndef MAIN_H
#define MAIN_H



#include "Base/config.h"
#include <iostream>
#include <string>
#include "Base/rendering.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 
#include <time.h>
#include "Base/utils.h"
#include "Base/events.h"
#include "Maps/Room.h"
#include "Maps/Map.h"
#include "Maps/MainMenu.h"
#include "Characters/Player.h"



using namespace std;

/// <summary>
/// Go to the main rendering loop of the game
/// </summary>
/// <param name="game">The game structure given by <code>initGame</code></param>
/// <returns></returns>
int playDoarm(GAME* game);

/// <summary>
/// Initialises the GAME structure.
/// </summary>
/// <returns></returns>
GAME* initGame();

#endif
