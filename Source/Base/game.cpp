#include "game.h"
#include "../Maps/Map.h"


/// <summary>
/// 
/// </summary>
unordered_map<pair<string, int>, Map*, PairHash> loadedMaps;

void changeMap(GAME* game, string worldname, int mapIndex, int startRoom)
{
	//Sauvegarde
	if (!isLoaded(game->worldName, *(game->currentMapId)))
		loadedMaps[{game->worldName, * (game->currentMapId)}] = game->currentMap;

	game->worldName = worldname;
	if (isLoaded(worldname, mapIndex))//déjà chargée en mémoire
	{
		game->currentMap = loadedMaps[{worldname, mapIndex}];
		game->currentMap->setCurrentRoom(startRoom);
	}
	else
	{
		*(game->currentMapId) = mapIndex;
		game->currentMap = new Map(worldname, *(game->player), *(game->renderer), game->currentMapId, startRoom);
		loadedMaps[{worldname, mapIndex}] = game->currentMap;
	}
}

bool isLoaded(string worldname, int mapIndex)
{
	return loadedMaps.find({ worldname, mapIndex }) != loadedMaps.end();
}

void freeMaps()
{
	for (auto& entry : loadedMaps)
	{
		try {

			//delete entry.second;
		}
		catch (...) {}
	}
	loadedMaps.clear();
}
