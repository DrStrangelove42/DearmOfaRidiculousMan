#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "config.h"

using namespace std;

static unordered_map<string, SDL_Texture*> textures;

SDL_Texture* LoadTexture(string id, SDL_Renderer* r);
int DumpError(string err);
void FreeTextures();
void DrawImage(SDL_Renderer * r, SDL_Texture* t, int x, int y, int w, int h);
int InitGame();

#endif