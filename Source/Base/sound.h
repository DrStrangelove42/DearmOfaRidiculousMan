#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include "config.h"
#include <unordered_map>
#include <iostream>

using namespace std;

/// <summary>
/// Initialises the audio interface.
/// If this fails, the game goes on without sound (we do not consider
/// audio failure as a breaking error).
/// </summary>
void SoundInit();

/// <summary>
/// Begin to play a song from the sound file given by the specified ID (id with MP3 extension added to it).
/// So far only the MP3 format is supported by DOARM (seems sufficient).
/// </summary>
/// <param name="soundId"></param>
/// <param name="loops">-1 by default (indefinitely).</param>
void SoundPlay(string soundId, int loops = 1);

/// <summary>
/// Exits the audio system and frees memory
/// </summary>
void SoundQuit();

#endif // !SOUND_H
