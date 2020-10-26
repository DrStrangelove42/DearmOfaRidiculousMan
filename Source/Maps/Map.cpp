#include "Map.h"
#include <SDL2/SDL.h>

Map::Map()
{

}

Map::~Map()
{
	/*Free memory*/
}

Map::Map(string file)
{

}

void render(SDL_Renderer renderer)
{
	rooms[currentRoom].render(renderer);
}

void tick(int time)
{
	rooms[currentRoom].tick(time);
}