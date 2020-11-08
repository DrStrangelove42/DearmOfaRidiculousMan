#include "config.h"

/*Size constants*/
int SZ_BLOCKSIZE = 20;
int SZ_SCREENWIDTH = 1000;
int SZ_SCREENHEIGHT = 800;

/*Current viewport*/
int BLOCKS_W = 50;	/* Max width of blocks on the screen */	
int BLOCKS_H = 40;	/* Max height of blocks on the screen */

/*The two following variables are only used in low level 
fonctions located in the <utils> module.*/
int VIEW_OFFSET_X = 0;
int VIEW_OFFSET_Y = 0;