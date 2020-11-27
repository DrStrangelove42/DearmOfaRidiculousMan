#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "config.h"
#include "Texture.h"
#include "RenderContext.h"
#include "rendering.h"

using namespace std;

class Player;

/// <summary>
/// Different states of the mouse.
/// </summary>
enum MOUSE_STATE
{
	MouseStateReleased, MouseStatePushed, MouseStateNone
};

/// <summary>
/// Button that is pressed.
/// </summary>
enum MOUSE_BUTTON
{
	MouseLeft, MouseRight, MouseMiddle, MouseNoButton
};

/// <summary>
/// 
/// </summary>
typedef struct
{
	int x;
	int y;
	MOUSE_STATE state;
	MOUSE_BUTTON button;
} MOUSE_DATA;



/// <summary>
/// The hashmap where textures are stored.
/// Textures beginning with 'text/' are reserved for text rendering.
/// </summary>
static unordered_map<string, Texture*> textures;

/* Use this function to load a texture from a BMP file. If it succeeds,
the texture is saved in <textures> and will be loaded from memory next
time this function is called for the same texture ID.*/
Texture* LoadTexture(string id, RenderContext& r);

/// <summary>
/// Builds a texture with the text inside.
/// </summary>
/// <param name="text"></param>
/// <param name="r"></param>
/// <param name="color"></param>
/// <returns></returns>
Texture* LoadString(string text, RenderContext& r, int color = 0xffffffff);

/// <summary>
/// Writes the error in the console output in a human-friendly way.
/// </summary>
/// <param name="err"></param>
/// <returns></returns>
int DumpError(string err);

/// <summary>
/// Frees memory.
/// </summary>
void FreeTextures();

/// <summary>
/// Initialisation of the <utils> module.
/// </summary>
/// <returns></returns>
int InitUtils();

/// <summary>
/// Returns the number of milliseconds since the beginning.
/// </summary>
/// <returns></returns>
int GetTime();

/// <summary>
/// Returns a random number in the interval [0, max[.
/// </summary>
/// <param name="max"></param>
/// <returns></returns>
int GetRandom(int max);
#endif
