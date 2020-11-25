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

enum KEY { Up, Down, Left, Right, A, W, B, Y, X, Other }; //TODO : what keys do we need ?

class Player;

/*
This structure is meant to be sent across game layers (starting from Map) when the user
types something to move or to perform an action.
*/
typedef struct
{
	int* currentRoom;		/* Pointer to the currentRoom field in the game engine. */
	int* currentMap;		/* if warp_IsExternal is set to true, indicates the map to load. */
	bool warp_IsExternal;	/* Tells the game that we need to go to another map. */
	KEY key;
	char keyLetter;
	Player* player;
	int destX;
	int destY;
} EVENT_ARGS;

enum MOUSE_STATE
{
	MouseStateReleased, MouseStatePushed, MouseStateNone
};

enum MOUSE_BUTTON
{
	MouseLeft, MouseRight, MouseMiddle, MouseNoButton
};

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

/* Writes the error in the console output in a human-friendly way. */
int DumpError(string err);

/* Frees memory. */
void FreeTextures();

/* Initialisation of the <utils> module. */
int InitUtils();

/* Returns the number of millisecond  */
int GetTime();

int GetRandom(int max);
#endif
