#include "Map.h"
#include <SDL2/SDL.h>

Map::Map()
{

}

Map::Map(string file)
{

}

void render(SDL_Renderer renderer)
{
	for (Room r : rooms)
	{
		r.render(renderer)
	}
}

void tick(int time)
{
	for (Room r : rooms)
	{
		r.tick(time)
	}
}