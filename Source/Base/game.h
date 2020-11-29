#ifndef GAME_H
#define GAME_H


#include "../Base/Window.h"

class Map;
class Player;
class RenderContext;

using namespace std;

/// <summary>
/// The type of keys associated with actions typed on the keyboard.
/// </summary>
enum KEY { Up, Down, Left, Right, A, W, B, Y, X, Other };

/// <summary>
/// A structure used to carry information about the current game.
/// </summary>
typedef struct
{
	/// <summary>
	/// A pointer to the window managed by SDL.
	/// </summary>
	Window* window;

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

	/// <summary>
	/// The key the player has pressed, so that we can perform the corresponding action. It is worth Other by default.
	/// </summary>
	KEY key;

	/// <summary>
	/// The character corresponding to the key pressed.
        /// This is different from Key, if for example the user is typing text to name a world for example.
        /// For keys with letters, it is the said letter.
	/// For the others (including numpad), this is not defined.
	/// </summary>
	char keyLetter;
} GAME;

#endif
