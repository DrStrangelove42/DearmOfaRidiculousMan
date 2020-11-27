#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include <string>
#include "../Maps/MainMenu.h"
#include "../Maps/Map.h"
#include "../Base/config.h"
#include "../Base/game.h"

using namespace std;

/// <summary>
/// The main procedure to manage events we receive from the user.
/// </summary>
/// <param name="game">The current game object.</param>
void manageEvents(GAME* game);

/// <summary>
/// Happens when a key is pushed.
/// </summary>
/// <param name="event">The underlying event structure.</param>
/// <param name="game">The current game object.</param>
EVENT_ARGS* onKeyDown(SDL_Event event, GAME* game, EVENT_ARGS* ea);

/// <summary>
/// Called on any event concerning the window.
/// </summary>
/// <param name="event">The underlying event structure.</param>
/// <param name="g">The current game object.</param>
void onWindowEvent(SDL_Event event, GAME* g);

/// <summary>
/// 
/// </summary>
/// <param name="event"></param>
/// <param name="game"></param>
void onMouseEvent(SDL_Event event, GAME* game);

/// <summary>
/// Destroy the game structure and quits the program.
/// </summary>
/// <param name="game">The current game object.</param>
void quitGame(GAME* game);
#endif
