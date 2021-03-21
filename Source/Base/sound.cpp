#include "sound.h"

unordered_map<string, Mix_Music*> loadedMus;

bool soundOk;

void SoundInit()
{
	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mix_Init failed with : " << Mix_GetError() << endl <<
			"Audio is therefore disabled" << endl;
		soundOk = false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == -1)
		{
			cout << "OpenAudio failed with : " << Mix_GetError() << endl <<
				"Audio is therefore disabled" << endl;
			soundOk = false;
		}
		else
			soundOk = true;
	}
}

void SoundPlay(string soundId, int loops)
{
	if (!soundOk) return;

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
	if (!soundOk) return;

	Mix_HaltMusic();
	for (auto& entry : loadedMus)
	{
		Mix_FreeMusic(entry.second);
	}
	Mix_CloseAudio();
	Mix_Quit();
}
