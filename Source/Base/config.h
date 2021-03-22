/*
CONFIG Module
Constant and preprocessor magic happen here.

For modules using MSWindows specific functions, this
file MUST be included first to avoid 'WIN' define problems
in case WIN6 only is defined.
*/

#ifndef CONFIG_H
#define CONFIG_H


/*
Preprocessor definitions for MS Windows only
*/
#ifdef WIN6
#define WIN 
#endif

#ifndef WIN
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif
#include <string>

using namespace std;

/*Size constants*/
/// <summary>
/// The size of a block, in pixels.
/// </summary>
extern int SZ_BLOCKSIZE;

/// <summary>
/// Width of the main Window.
/// </summary>
extern int SZ_MAINWIDTH;

/// <summary>
/// Width of the window, in pixels.
/// </summary>
extern int SZ_SCREENWIDTH;

/// <summary>
/// Height of the Window, in pixels.
/// </summary>
extern int SZ_SCREENHEIGHT;

/// <summary>
/// Width of the player Window, in pixels.
/// </summary>
extern int SZ_INFOSWIDTH;

/// <summary>
/// Delay, in ms, between each game loop.
/// </summary>
extern int WAIT_TIME;

/*Current viewport*/
/// <summary>
/// Max width of <see cref="Block">Blocks</see> on the screen.
/// </summary>
extern int BLOCKS_W;

/// <summary>
/// Max height of <see cref="Block">Blocks</see> on the screen.
/// </summary>
extern int BLOCKS_H;

/// <summary>
/// Variable only used in low level functions located in the utils module.
/// </summary>
extern int VIEW_OFFSET_X;

/// <summary>
/// Variable only used in low level functions located in the utils module.
/// </summary>
extern int VIEW_OFFSET_Y;

/// <summary>
/// Extensions for Worlds and <see cref="Map">Maps</see>.
/// </summary>
extern string EXT;

/// <summary>
/// The extension used for text files describing stories in Story Mode.
/// </summary>
extern string STORYFILES_EXT;

/// <summary>
/// Location of files describing Worlds.
/// </summary>
extern string WORLDFILES_LOCATION;

/// <summary>
/// Location of files describing stories in Story Mode.
/// </summary>
extern string STORYFILES_LOCATION;

/// <summary>
/// Location of files generated to describe Worlds.
/// </summary>
extern string WORLDDATA_LOCATION;

/// <summary>
/// Location of files used to save progress.
/// </summary>
extern string SAVES_LOCATION;

/// <summary>
/// Absolute path to the data folder. This must have a trailing slash.
/// </summary>
extern string DATA_LOCATION;

/// <summary>
/// Absolute path to the text resources folder. This must have a trailing slash.
/// </summary>
extern string LANG_LOCATION;

/// <summary>
/// Extension of language files
/// </summary>
extern string LANGFILES_EXT;

/// <summary>
/// Current language identifier in the game.
/// </summary>
extern string LANGUAGE;

#endif


