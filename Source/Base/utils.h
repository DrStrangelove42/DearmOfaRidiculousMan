#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

#include "config.h"

#include "RenderContext.h"

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
/// Writes the error in the console output in a human-friendly way.
/// </summary>
/// <param name="err"></param>
/// <returns></returns>
int DumpError(string err);

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

/// <summary>
/// Returns the first token.
/// </summary>
/// <param name="line"></param>
/// <param name="sep"></param>
/// <returns></returns>
string NextToken(string& line, char sep = ' ');

/// <summary>
/// Returns the first token, and go forward in the string.
/// </summary>
/// <param name="line"></param>
/// <param name="sep"></param>
/// <returns></returns>
string EatToken(string& line, char sep = ' ');

/// <summary>
/// Loads a string from the current language context.
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
string GetText(string id);

/// <summary>
/// Initialisation of the current language context.
/// </summary>
/// <param name="langCode"></param>
void LoadTextFromLanguage(string& langCode);
#endif
