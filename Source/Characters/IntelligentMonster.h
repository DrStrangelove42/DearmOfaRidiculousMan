#ifndef INTELLIGENTMONSTER_H
#define INTELLIGENTMONSTER_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include "Monster.h"

using namespace std;

class Room;

class IntelligentMonster : public Monster
{
protected:
        /// <summary>
	/// h is the heuristic function, it tells us the length of an optimal path from position (x,y) to (destX, destY) if all blocks were traversable.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
        int h(int x, int y);

	/// <summary>
	/// Reconstructs the optimal path according to the predecessor matrix pred, and stores it in path.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="pred"></param>	
	void reconstructPath(int* &path, int** pred);
	
	struct queueCompare
	{
	        bool operator()(const int* args1, const int* args2)
	        {
		        return args1[0] > args2[0];
		}
	};
	
	void optimalPath(int* &path, bool** trav);

	/// <summary>
	/// A boolean that tells us whether we allow the monster to move diagonally in the room or not.
	/// </summary>
	bool diagMovement;
	
	/// <summary>
	/// The x coordinate of the destination of the monster, which will be updated to be equal to that of the player.
	/// </summary>
	int destX;

	/// <summary>
	/// The y coordinate of the destination of the monster, which will be updated to be equal to that of the player.
	/// </summary>
	int destY;

	/// <summary>
	/// Width of the room.
	/// </summary>
	int width;

	/// <summary>
	/// Height of the room.
	/// </summary>
	int height;
	
	/// <summary>
	/// The optimal path to (destX,destY).
	/// </summary>
	int* path;

	/// <summary>
	/// The number of steps in the optimal path to (destX,destY).
	/// </summary>
	int pathLength;

	
	/// <summary>
	/// The step (between 0 and pathLength-1) the monster is up to in the optimal path to (destX,destY).
	/// </summary>
	int pathStep;
public:
	IntelligentMonster(RenderContext& renderer,
			   Player& p,
			   Room& r,
			   string textureId,
			   int health,
			   int dmg,
			   int atkDelay = 1000,
			   int atkRadius = 1,
			   int coins = 200,
			   int exp = 50,
			   int moveDelay = 500,
			   bool alarmed = false,
			   bool diagMovement = true);

	~IntelligentMonster();
	virtual void tick(int time, GAME* game);
};
#endif
