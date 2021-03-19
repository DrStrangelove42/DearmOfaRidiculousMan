#include "sound.h"

unordered_map<string, Mix_Music*> loadedMus;

void SoundInit()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
}

void SoundPlay(string soundId, int loops)
{
	if (loadedMus.find(DATA_LOCATION + "Res/Audio/" + soundId + ".mp3") == loadedMus.end())
	{
		Mix_Music* music;
		music = Mix_LoadMUS((DATA_LOCATION + "Res/Audio/" + soundId + ".mp3").c_str());
		
		loadedMus[soundId] = music;
	}

	Mix_PlayMusic(loadedMus[soundId], loops);
}

void SoundQuit()
{
	Mix_HaltMusic();
	for (auto& entry : loadedMus)
	{
		Mix_FreeMusic(entry.second);
	}
	Mix_CloseAudio();
	Mix_Quit();
}
