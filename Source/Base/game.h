#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../Maps/Map.h"


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

#endif