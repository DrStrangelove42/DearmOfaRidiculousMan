#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include "config.h"
#include <unordered_map>

using namespace std;

void SoundInit();

void SoundPlay(string soundId, int loops = 1);

void SoundQuit();

#endif // !SOUND_H
