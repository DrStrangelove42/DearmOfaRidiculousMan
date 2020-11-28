#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

extern bool DEBUG_MODE;

/*Size constants*/
extern int SZ_BLOCKSIZE;	/* The size of a block, in pixels */
extern int SZ_SCREENWIDTH;	/* Width of the window, in pixels */
extern int SZ_SCREENHEIGHT;	/* Height of the window, in pixels */

/*Current viewport*/
extern int BLOCKS_W;	/* Max width of blocks on the screen */
extern int BLOCKS_H;	/* Max height of blocks on the screen */

/*The two following variables are only used in low level
fonctions located in the <utils> module.*/
extern int VIEW_OFFSET_X;
extern int VIEW_OFFSET_Y;

extern string WORLDFILE_EXT;
extern string MAPFILE_EXT;
extern string MAPFILES_LOCATION;
#endif