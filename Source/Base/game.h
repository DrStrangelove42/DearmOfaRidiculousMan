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

/// <summary>
/// Change map function.
/// </summary>
/// <param name="game"></param>
/// <param name="mapIndex">-1 : auto mode</param>
/// <param name="worldname"></param>
/// <param name="startMap"></param>
/// <param name="startRoom"></param>
void changeMap(GAME* game, string worldname, int mapIndex = -1, int startRoom = -1);

/// <summary>
/// 
/// </summary>
void freeMaps();

/// <summary>
/// Returns true if the map is already loaded in the map cache.
/// </summary>
/// <param name="worldname"></param>
/// <returns></returns>
bool isLoaded(string worldname, int mapIndex);

/// <summary>
/// Frees resources associated with the map.
/// </summary>
/// <param name="worldname"></param>
/// <param name="mapIndex"></param>
void destroyMap(string worldname, int mapIndex);

/// <summary>
/// Adds manually the map to the cache (in case of special map)
/// </summary>
/// <param name="worldName"></param>
/// <param name="mapIndex"></param>
/// <param name="map"></param>
void addMapToCache(string worldName, int mapIndex, Map* map);

struct PairHash
{
	size_t operator()(const pair<string, int>& o) const
	{
		return hash<string>()(o.first + to_string(o.second));
	}
};
#endif
