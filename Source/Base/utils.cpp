#include "utils.h"

using namespace std;

/*
This file is for helpers functions. All functions in this file (and only these
ones) begin with a capital letter.
*/

int InitUtils()
{
	//Do some initialisation ?

	return 0;
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