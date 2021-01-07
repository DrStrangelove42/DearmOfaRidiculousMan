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

class Room; class Map;

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
	void reconstructPath(int*& path, int** pred);

	struct queueCompare
	{
		bool operator()(const int* args1, const int* args2)
		{
			return args1[0] > args2[0];
		}
	};

	void optimalPath(int*& path, bool** trav);

	/// <summary>
	/// A boolean that tells us whether we allow the monster to move diagonally in the room or not.
	/// </summary>
	bool diagMovement;

	/// <summary>
	/// The x coordinate of the current destination of the monster, updtaed to <code>newDestX</code> every moveDelay number of ticks. This helps us compute the optimal path only when the destination has changed since the last move.
	/// </summary>
	int destX;

	/// <summary>
	/// The y coordinate of the current destination of the monster, updtaed to <code>newDestY</code> every moveDelay number of ticks. This helps us compute the optimal path only when the destination has changed since the last move.
	/// </summary>
	int destY;

	/// <summary>
	/// The x coordinate of the wanted destination of the monster, updated every tick.
	/// </summary>
	int newDestX;

	/// <summary>
	/// The y coordinate of the wanted destination of the monster, updated every tick.
	/// </summary>
	int newDestY;

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

	/// <summary>
	/// When the player warps to another room, the information is stored in this queue so that the monster follows the player. When a player uses a warp, we add successively to this queue the x and y coordinate of the warp, then the room, x and y coordinates of the destination. Note that an intelligent monster only follows the player within the same map. 
	/// </summary>
	queue<int> warpInfo;
	
public:
	IntelligentMonster(RenderContext& renderer,
		Player& p,
		Room* r,
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

	/// <summary>
	/// Adds the necessary information to <code>warpInfo</code> when the player warps, taking into account whether or not the player just left the room the monster is in.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	/// <param name="playerJustLeft"></param>
	void sendMonsterToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft);

	/// <summary>
	/// Empties the queue <code>warpInfo</code>, this is for when the player and the monster are in the same room.
	/// </summary>
	void cleanMonsterWarpInfo();
};
#endif
