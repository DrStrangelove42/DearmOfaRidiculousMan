#include "config.h"

/*Size constants*/
int SZ_BLOCKSIZE = 20;
int SZ_INFOSWIDTH = 300;
int SZ_MAINWIDTH = 1000;
int SZ_SCREENWIDTH = SZ_MAINWIDTH + SZ_INFOSWIDTH;
int SZ_SCREENHEIGHT = 800;

int WAIT_TIME = 50;

/*Current viewport*/
int BLOCKS_W = 50;	/* Max width of blocks on the screen */
int BLOCKS_H = 40;	/* Max height of blocks on the screen */

/*The two following variables are only used in low level
fonctions located in the <utils> module.*/
int VIEW_OFFSET_X = 0;
int VIEW_OFFSET_Y = 0;

/// <summary>
/// The extension used for text files describing worlds or maps.
/// </summary>
string EXT = ".txt";

#ifdef DEBUG_MODE
string DATA_LOCATION = "./";
#else
#ifdef WIN
string _getenv()
{
	char* buf = nullptr;
	size_t sz = 0;
	string ret = "";
	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		ret = string(buf);
		free(buf);
	}
	return ret;
}
string DATA_LOCATION = _getenv() + "/Doarm/";
#else
string DATA_LOCATION = string(getenv("HOME") == NULL ? getpwuid(getuid())->pw_dir : getenv("HOME")) + "/.doarm/";
#endif
#endif

string WORLDFILES_LOCATION = DATA_LOCATION + "Res/Worlds/";

string STORYFILES_LOCATION = DATA_LOCATION + "Res/StoryMode/";

string STORYFILES_EXT = ".txt";

string WORLDDATA_LOCATION = DATA_LOCATION + "Data/Worlds/";

string SAVES_LOCATION = DATA_LOCATION + "Data/Saves/";

string LANGFILES_EXT = ".txt";
string LANG_LOCATION = DATA_LOCATION + "Res/Text/";
string LANGUAGE = "en-uk";