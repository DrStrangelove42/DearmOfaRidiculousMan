#include "config.h"

bool DEBUG_MODE = true;

/*Size constants*/
int SZ_BLOCKSIZE = 20;
int SZ_SCREENWIDTH = 1000;
int SZ_SCREENHEIGHT = 800;
int SZ_INFOSWIDTH = 300;
/*Current viewport*/
int BLOCKS_W = 50;	/* Max width of blocks on the screen */
int BLOCKS_H = 40;	/* Max height of blocks on the screen */

/*The two following variables are only used in low level
fonctions located in the <utils> module.*/
int VIEW_OFFSET_X = 0;
int VIEW_OFFSET_Y = 0;

/// <summary>
/// The extension used for files containing wolds
/// </summary>
string WORLDFILE_EXT = ".txt";

/// <summary>
/// The extension of map files.
/// </summary>
string MAPFILE_EXT = ".txt";

/// <summary>
/// Location of maps
/// </summary>
string MAPFILES_LOCATION = "./Source/MapCreation/TestMaps/";