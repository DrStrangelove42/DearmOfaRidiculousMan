#include "IntelligentMonster.h"
#include "../Maps/Room.h"
#include "../Maps/Map.h"

IntelligentMonster::IntelligentMonster(RenderContext& renderer,
	Player& p,
	Room* r,
	string textureId,
	int health,
	int dmg,
	int atkDelay,
	int atkRadius,
	int coins,
	int exp,
	int moveDelay,
	bool alarmed,
	bool diagMovement) : Monster(renderer, p, r, textureId, health, dmg, atkDelay, atkRadius, coins, exp, moveDelay, alarmed), diagMovement(diagMovement), destX(-1), destY(-1), path(NULL)
{

}

IntelligentMonster::~IntelligentMonster()
{

}

int IntelligentMonster::h(int x, int y)
{
	if (diagMovement)
		return max(abs(x - destX), abs(y - destY));
	else
		return abs(x - destX) + abs(y - destY);
}

void IntelligentMonster::reconstructPath(int*& path, int** pred)
{
	int* optPath = new int[2 * pathLength];
	int currentX = destX;
	int currentY = destY;
	// We start with (destX, destY), then work our way backwards to (startX, startY) thanks to pred. 
	for (int i = pathLength - 1; i >= 0; i--)
	{
		int movementX = pred[currentX][2 * currentY];
		int movementY = pred[currentX][2 * currentY + 1];
		optPath[2 * i] = movementX;
		optPath[2 * i + 1] = movementY;
		currentX = currentX - movementX;
		currentY = currentY - movementY;
	}
	path = optPath;
}

void IntelligentMonster::optimalPath(int*& path, bool** trav)
{
	int width = room->getW();
	int height = room->getH();
	int startX = x, startY = y;
	int numberOfDirs = (diagMovement ? 8 : 4);
	//The number of directions the monster can potentially  move in from any block (8 if we allow diagonal movement, 4 if we don't).

	int dirs[16] = { 0,-1,1,0,0,1,-1,0,1,-1,1,1,-1,1,-1,-1 };
	//dirs is an array representing the different directions the monster can move in. For each i < numberOfDirs, a direction is represented by its relative movement along the x axis in dir[2*i] and along its y axis in dir[2*i+1]. The first four movements represented are North, East, South and West, and the last four are the diagonal movements. Therefore, if numberOfDirs is 4, the diagonal movements won't be considered.

	int** pred = new int* [width];

	for (int i = 0; i < width; i++)
	{
		pred[i] = new int[2 * height];
	}
	// For a block (x,y), if (pred[x}[2*y],pred[x][2*y+1]) has been defined then it is the movement that was used to get to (x,y) from its predecessor in an optimal path from (startX,startY) to (x,y). The predecessor of (x,y) in this optimal path from (startX,startY) to (x,y) is therefore (x-pred[x}[2*y],y-pred[x][2*y+1]). This array will be used to construct an optimal path when the destination is reached.

	bool** discovered = new bool* [width];

	for (int i = 0; i < width; i++)
	{
		discovered[i] = new bool[height];
		for (int j = 0; j < height; j++)
		{
			discovered[i][j] = false;
		}
	}
	discovered[startX][startY] = true;
	// For a block (x,y), discovered[x][y] tells us whether the algorithm has discovered block (x,y) yet or not.

	priority_queue <int*, vector<int*>, queueCompare> openSet;
	// openSet contains the blocks that the algorithm is still considering as well as there expected cost. Each of its elements is an array of integers of size 3, where the first element is the expected cost (which is the number of steps of the algorithm to reach (x,y) plus h(x,y)), the second is the x coordinate, and the third is the y coordinate. The fuction queueCompare is defined such that the element with the smallest expected cost is popped when calling pop.

	int* topush = new int[3];
	topush[0] = h(startX, startY);
	topush[1] = startX;
	topush[2] = startY;
	openSet.push(topush);

	int currentStep;

	bool foundPath = false;

	while (!(openSet.empty()))
	{
		int* currentBlock = openSet.top();
		openSet.pop();
		int currentBlockX = currentBlock[1], currentBlockY = currentBlock[2];

		// We compute the number of steps that it took to get to this block: in openSet we store the number of steps plus the h of the block so we can get it by subtracting.
		currentStep = currentBlock[0] - h(currentBlockX, currentBlockY);

		if (currentBlockX == destX && currentBlockY == destY)
		{
			pathLength = currentStep;
			reconstructPath(path, pred);
			foundPath = true;
			break;
		}
		currentStep++;
		for (int i = numberOfDirs - 1; i >= 0; i--)
		{
			// For each of the directions possible, we look at the current block's neighbour in that direction. If that block is in the room, is traversable, and hasn't yet been discovered, we have discovered a new shortest path from the starting position to this block, we therefore update pred and discovered accordingly, and add the block to the open set with the correct estimated cost.
			int nextBlockX = currentBlockX + dirs[2 * i];
			int nextBlockY = currentBlockY + dirs[2 * i + 1];
			if (nextBlockX >= 0 && nextBlockX < width && nextBlockY >= 0 && nextBlockY < height && trav[nextBlockX][nextBlockY] && !discovered[nextBlockX][nextBlockY])
			{
				discovered[nextBlockX][nextBlockY] = true;
				pred[nextBlockX][2 * nextBlockY] = dirs[2 * i];
				pred[nextBlockX][2 * nextBlockY + 1] = dirs[2 * i + 1];
				int* topush = new int[3];
				topush[0] = currentStep + h(nextBlockX, nextBlockY);
				topush[1] = nextBlockX;
				topush[2] = nextBlockY;
				openSet.push(topush);
			}
		}
	}
	// If we exit the while loop because openSet is empty, then there is no path from (startX,startY) to (destX,destY), we therefore make path the array containing only 0.
	if (!foundPath)
	{
		pathLength = 0;
	}

	for (int i = 0; i < width; i++)
	{
		delete[] pred[i];
		delete[] discovered[i];
	}

	delete[] pred;
	delete[] discovered;
}

void IntelligentMonster::tick(int time, GAME* game)
{
	if (!isAlive()) return;

	if (warpInfo.empty()) // i.e. If the monster is in the same room as the player, otherwise newDestX and newDestY have been updated by the warp taken by the player or when the monster is warped.
	{
		newDestX = player.getX();
		newDestY = player.getY();
	}
	
	if (time - lastTimeAtk >= attackDelay)
	{
		lastTimeAtk = time;
		manageAlarm();
		attackRound();
	}
	if (time - lastTimeMv >= moveDelay)
	{
		// We only compute the monster's path if its destination has changed since its last move.
		if (destX != newDestX || destY != newDestY)
		{
			destX = newDestX;
			destY = newDestY;
			int width = room->getW();
			int height = room->getH();
			bool** trav = new bool* [width];
			for (int i = 0; i < width; i++)
			{
				trav[i] = new bool[height];
				for (int j = 0; j < height; j++)
				{
					trav[i][j] = room->isTraversable(i, j);
				}
			}
			optimalPath(path, trav);
			pathStep = 0;
			for (int i = 0; i < width; i++)
			{
				delete[] trav[i];
			}
			delete[] trav;
		}
		if (pathStep < pathLength)
		{
			room->tryTeleportAt(*this, x + path[2 * pathStep], y + path[2 * pathStep + 1]);
			pathStep++;
		}
		else if (!(warpInfo.empty())) //We have arrived on the warp
		{
			moveToRoom(game->currentMap->getRooms()[warpInfo.front()]);
			warpInfo.pop();
			int warpX = warpInfo.front();
			warpInfo.pop();
			int warpY = warpInfo.front();
			warpInfo.pop();
			room->tryTeleportAt(*this, warpX, warpY);
			if (!(warpInfo.empty())) //warpInfo contains a new warp destination in this new room we've moved to
			{
				newDestX = warpInfo.front();
				warpInfo.pop();
				newDestY = warpInfo.front();
				warpInfo.pop();
			}
		}
		lastTimeMv = time;
	}
}

void IntelligentMonster::sendMonsterToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft)
{
	if (playerJustLeft)
	{
		newDestX = x;
		newDestY = y;
	}
	else
	{
		warpInfo.push(x);
		warpInfo.push(y);
	}
	warpInfo.push(destRoom);
	warpInfo.push(destX);
	warpInfo.push(destY);
}

void IntelligentMonster::cleanMonsterWarpInfo()
{
	while (!(warpInfo.empty()))
	{
		warpInfo.pop();
	}
}
