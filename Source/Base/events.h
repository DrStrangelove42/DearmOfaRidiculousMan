#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include <string>
#include "../Maps/Map.h"
#include "../Base/config.h"

using namespace std;

/// <summary>
/// A structure used to carry information about the current game.
/// </summary>
typedef struct
{
	/// <summary>
	/// A pointer to the window managed by SDL.
	/// </summary>
	SDL_Window* window;

	/// <summary>
	/// Our graphics context.
	/// </summary>
	RenderContext* renderer;

	/// <summary>
	/// Name of the world in which we are playing at the moment.
	/// </summary>
	string worldName;

	/// <summary>
	/// A pointer to the current map.
	/// </summary>
	Map* currentMap;

	/// <summary>
	/// This pointer is used in non-local warps to change the map.
	/// </summary>
	int* currentMapId;

	/// <summary>
	/// The player
	/// </summary>
	Player* player;

	/// <summary>
	/// If set to true, implies the end of the game.
	/// </summary>
	bool quit;
} GAME;



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
void onKeyDown(SDL_Event event, GAME* game);

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
