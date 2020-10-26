#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <string>
#include <map>

using namespace std;

unordered_map<string, SDL_Texture*> textures;

SDL_Texture LoadTexture(string id);
void DumpError(string err);
void FreeTextures();
void DrawImage(SDL_Renderer r, SDL_Texture* t, int x, int y, int w, int h);

#endif