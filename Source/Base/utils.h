#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <unordered_map>
#include "config.h"
#include "Texture.h"
#include "RenderContext.h"
#include "rendering.h"

using namespace std;

/* The hashmap where textures are stored. */
static unordered_map<string, Texture*> textures;

/* Use this function to load a texture from a BMP file. If it succeeds,
the texture is saved in <textures> and will be loaded from memory next
time this function is called for the same texture ID.*/
Texture* LoadTexture(string id, RenderContext& r);

/* Writes the error in the console output in a human-friendly way. */
int DumpError(string err);

/* Frees memory. */
void FreeTextures();

/* Initialisation of the <utils> module. */
int InitUtils();

#endif