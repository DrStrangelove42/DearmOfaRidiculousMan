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
	/// A pointer to the Window managed by SDL.
	/// </summary>
	Window* window;

	/// <summary>
	/// A pointer to the RenderContext that contains all the graphical information.
	/// </summary>
	RenderContext* renderer;

	/// <summary>
	/// Name of the World in which we are playing at the moment.
	/// </summary>
	string worldName;

	/// <summary>
	/// A pointer to the current Map.
	/// </summary>
	Map* currentMap;

	/// <summary>
	/// A pointer used in non-local <see cref="Warp">Warps</see> to change the Map.
	/// </summary>
	int* currentMapId;

	/// <summary>
	/// The Player.
	/// </summary>
	Player* player;

	/// <summary>
	/// Indicates whether or not the game should be ended.
	/// </summary>
	bool quit;

	/// <summary>
	/// The key the user has pressed, so that we can perform the corresponding action. It is worth Other by default.
	/// </summary>
	KEY key;

	/// <summary>
	/// The character corresponding to the key pressed.
	/// This is different from the <see cref="GAME::key">key</see>, if the user is typing text to name a world for example.
	/// For keys with letters, it is the said letter.
	/// For the others (including numpad), this is not defined.
	/// </summary>
	char keyLetter;
} GAME;

/// <summary>
/// Changes the current Map.
/// </summary>
/// <param name="game"></param>
/// <param name="mapIndex">-1 : auto mode</param>
/// <param name="worldname"></param>
/// <param name="startMap"></param>
/// <param name="startRoom"></param>
void changeMap(GAME* game, string worldname, int mapIndex = -1, int startRoom = -1);

/// <summary>
/// Deletes all the <see cref="Map">Maps</see> that were used and not freed.
/// </summary>
void freeMaps();

/// <summary>
/// Indicates whether or not the Map is already loaded in the map cache.
/// </summary>
/// <param name="worldname"></param>
/// <returns></returns>
bool isLoaded(string worldname, int mapIndex);

/// <summary>
/// Frees all the resources associated with the Map.
/// </summary>
/// <param name="worldname"></param>
/// <param name="mapIndex"></param>
void destroyMap(string worldname, int mapIndex);

/// <summary>
/// Adds manually the Map to the cache (in case of special Map).
/// </summary>
/// <param name="worldName"></param>
/// <param name="mapIndex"></param>
/// <param name="map"></param>
void addMapToCache(string worldName, int mapIndex, Map* map);

/// <summary>
/// The hash function used to store the <see cref="Map">Maps</see> in the cache.
/// </summary>
struct PairHash
{
	size_t operator()(const pair<string, int>& o) const
	{
		return hash<string>()(o.first + to_string(o.second));
	}
};
#endif
