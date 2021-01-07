#include "game.h"
#include "../Maps/Map.h"


/// <summary>
/// 
/// </summary>
unordered_map<string, Map*> loadedMaps;

void changeMap(GAME* game, string worldname, int* startMap, int startRoom)
{
	//Sauvegarde
	if (!isLoaded(game->worldName))
		loadedMaps[game->worldName] = game->currentMap;

	game->worldName = worldname;
	if (loadedMaps.find(worldname) != loadedMaps.end())//déjà chargée en mémoire
	{
		game->currentMap = loadedMaps[worldname];
	}
	else
	{
		*(game->currentMapId) = -1;
		game->currentMap = new Map(worldname, *(game->player), *(game->renderer), game->currentMapId);
		loadedMaps[worldname] = game->currentMap;
	}
}

bool isLoaded(string worldname)
{
	return loadedMaps.find(worldname) != loadedMaps.end();
}

void freeMaps()
{
	for (auto& entry : loadedMaps)
	{
		delete entry.second;
	}
	loadedMaps.clear();
}
