#include "Room.h"
#include <SDL2/SDL.h>

Room(int width, int height)
{

}

~Room()
{

}

void render(SDL_Renderer renderer)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; i++)
		{
			blocks[i][j].render(renderer);
		}
	}
}