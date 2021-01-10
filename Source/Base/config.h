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

#include <string>

using namespace std;

/*Size constants*/
extern int SZ_BLOCKSIZE;	/* The size of a block, in pixels */
extern int SZ_MAINWIDTH;
extern int SZ_INFOSWIDTH;
extern int SZ_SCREENWIDTH;	/* Width of the window, in pixels */
extern int SZ_SCREENHEIGHT;	/* Height of the window, in pixels */
extern int SZ_INFOSWIDTH;	/* Width of the player window, in pixels */

/// <summary>
/// Delay, in ms, between each game loop.
/// </summary>
extern int WAIT_TIME;

/*Current viewport*/
extern int BLOCKS_W;	/* Max width of blocks on the screen */
extern int BLOCKS_H;	/* Max height of blocks on the screen */

/*The two following variables are only used in low level
fonctions located in the <utils> module.*/
extern int VIEW_OFFSET_X;
extern int VIEW_OFFSET_Y;

/// <summary>
/// Extensions for worlds and maps
/// </summary>
extern string EXT;
/// <summary>
/// The extension used for text files describing stories in Story Mode.
/// </summary>
extern string STORYFILES_EXT;
/// <summary>
/// Location of files describing worlds.
/// </summary>
extern string WORLDFILES_LOCATION;

/// <summary>
/// Location of files describing stories in Story Mode.
/// </summary>
extern string STORYFILES_LOCATION;

/// <summary>
/// Location of files generated to describe worlds.
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
