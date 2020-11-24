#include "utils.h"

using namespace std;

/*
This file is for helpers functions. All functions in this file (and only these
ones) begin with a capital letter.
*/

int InitUtils()
{
	srand(static_cast<unsigned int>(time(NULL)));

	return 0;
}

/*
Returns a pseudo-random number in [0, max[.
*/
int GetRandom(int max)
{
	return rand() % max;
}

/*
Loads the texture with the specified identifier.
*/
Texture* LoadTexture(string id, RenderContext& renderer)
{
	if (textures.find(id) == textures.end())
		textures[id] = new Texture(renderer, id);

	return textures[id];
}

Texture* LoadString(string text, RenderContext& r)
{
	string id = "text/" + text;
	if (textures.find(id) == textures.end())
	{
		//Not rendered yet
		SDL_Color White = { 255, 255, 255, 255 };
		SDL_Surface* s = TTF_RenderText_Solid(FONT, text.c_str(), White);
		SDL_Texture* t = r.fromSurface(s);

		int w, h;
		if (TTF_SizeText(FONT, text.c_str(), &w, &h))
		{
			cout << TTF_GetError() << endl;
			return NULL;
		}

		textures[id] = new Texture(t, w, h);
	}

	return textures[id];
}

void FreeTextures()
{
	for (auto& entry : textures)
	{
		cout << "Freeing " << entry.first << endl;
		delete entry.second;
	}
	textures.clear();
}

int DumpError(string err)
{
	cout << "Error : " << err << "\nInternal error: " << renderErrorDetails() << endl;
	return EXIT_FAILURE;
}

int GetTime()
{
	using namespace std::chrono;
	static high_resolution_clock::time_point referenceTime = high_resolution_clock::now();
	high_resolution_clock::time_point n = high_resolution_clock::now();
	duration<double, milli> time_span = n - referenceTime;
	return (int)time_span.count();
}