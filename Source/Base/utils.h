#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "config.h"

using namespace std;

/* The hashmap where textures are stored. */
static unordered_map<string, SDL_Texture*> textures;

/* Use this function to load a texture from a BMP file. If it succeeds,
the texture is saved in <textures> and will be loaded from memory next
time this function is called for the same texture ID.*/
SDL_Texture* LoadTexture(string id, SDL_Renderer* r);

/* Writes the error in the console output in a human-friendly way. */
int DumpError(string err);

/* Frees memory. */
void FreeTextures();

/* Draw an image (a SDL_Texture). */
void DrawImage(SDL_Renderer * r, SDL_Texture* t, int x, int y, int w, int h);

/* Initialisation of the <utils> module. */
int InitGame();

#endif