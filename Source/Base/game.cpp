#include "game.h"
#include "../Maps/Map.h"


/// <summary>
/// Maps that have already been loaded.
/// </summary>
unordered_map<pair<string, int>, Map*, PairHash> loadedMaps;

void changeMap(GAME* game, string worldname, int mapIndex, int startRoom)
{
	//Saving
	int prev_mapIndex = *(game->currentMapId);
	string prev_world = game->worldName;
	if (!isLoaded(game->worldName, *(game->currentMapId)))//In case of manually loaded
		loadedMaps[{game->worldName, * (game->currentMapId)}] = game->currentMap;

	game->worldName = worldname;
	if (isLoaded(worldname, mapIndex))
	{
		game->currentMap = loadedMaps[{worldname, mapIndex}];
		game->currentMap->setCurrentRoom(startRoom);
		*(game->currentMapId) = mapIndex;
		if (worldname != "EndCredits" && mapIndex < 0)
		{
			//If we are on map -1, but it is already loaded, it means that the player is positionned automatically.
			//As we do not create the map, the player is not teleported where it shoud be.
			//So we manually ask the map to teleport it, and we refresh the map index.
			mapIndex = 0;
			*(game->currentMapId) = 0;
			game->currentMap->teleportPlayerOnStart();
		}
	}
	else
	{
		*(game->currentMapId) = mapIndex;
		game->currentMap = new Map(worldname, *(game->player), *(game->renderer), game->currentMapId, startRoom);
		if (mapIndex == -1)//TODO
		{
			//Same reasons as above
			mapIndex = 0;
			*(game->currentMapId) = 0;
		}
		if (game->currentMap->getRoomCount() <= 0)
		{
			//Problem in map loading, rollback
			*(game->currentMapId) = prev_mapIndex;
			game->currentMap = loadedMaps[{prev_world, * (game->currentMapId)}];
		}
		else
		{
			loadedMaps[{worldname, mapIndex}] = game->currentMap;
			*(game->currentMapId) = mapIndex;
		}
	}
}

bool isLoaded(string worldname, int mapIndex)
{
	return loadedMaps.find({ worldname, mapIndex }) != loadedMaps.end();
}

void destroyMap(string worldname, int mapIndex)
{

	if (isLoaded(worldname, mapIndex))
	{
		delete loadedMaps[{worldname, mapIndex}];
		loadedMaps.erase({ worldname, mapIndex });
	}
	else if (mapIndex == 0)
	{
		//test on -1
		destroyMap(worldname, -1);
	}
}

void addMapToCache(string worldName, int mapIndex, Map* map)
{
	if (!isLoaded(worldName, mapIndex))
		loadedMaps[{worldName, mapIndex}] = map;
}

void freeMaps()
{
	for (auto& entry : loadedMaps)
	{
		delete entry.second;
	}
	loadedMaps.clear();
}
