#include "utils.h"

/*
This file is for helpers functions. All functions in this file (and only these
ones) begin with a capital letter.
*/

/*
Loads the texture with the specified identifier.
*/
SDL_Texture* LoadTexture(string id)
{
	SDL_Texture* tx = NULL;
	SDL_Surface* bmp = NULL;

	if (textures.find(id) != textures.end())
		tx = textures[id];
	else
	{
		bmp = SDL_LoadBMP((id + ".bmp").c_str());
		SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xff, 0, 0xff));

		if (NULL == bmp)
			DumpError("Unable to load texture #" + id);

		tx = SDL_CreateTextureFromSurface(renderer, bmp);
		SDL_FreeSurface(bmp);

		if (NULL == tx)
			DumpError("Unable to create texture #" + id);

		textures[id] = tx;
	}

	return tx;
}

void FreeTextures()
{
	for (auto& entry : textures)
		SDL_DestroyTexture(entry);
}

void DrawImage(SDL_Renderer r, SDL_Texture* t, int x, int y, int w, int h)
{
	if (NULL != t) 
	{
		SDL_Rect dst = { x, y, w, h };
		SDL_RenderCopy(r, t, NULL, &dst);
	}
}

void DumpError(string err)
{
	std::cout << "Error : " << err << "\nInternal error: " << SDL_GetError() << endl;
}