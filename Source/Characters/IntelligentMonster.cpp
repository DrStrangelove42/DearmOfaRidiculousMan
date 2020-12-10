#include "IntelligentMonster.h"

int IntelligentMonster::h(bool diagMovement, int x, int y, int destX, int destY)
{
        if (diagMovement)
	        return max(abs(x-destX),abs(y-destY));
	else
	        return abs(x-destX) + abs(y-destY);
}
//h is the heuristic function, it tells us the length of an optimal path from position (x,y) to (destX, destY) if all blocks were traversable.

void IntelligentMonster::reconstructPath(int* &path, int** pred, int numberOfSteps, int destX, int destY)
{
        int* optPath = new int[2*numberOfSteps + 1];
	optPath[0] = numberOfSteps;
	int currentX = destX;
	int currentY = destY;
	// We start with (destX, destY), then work our way backwards to (startX, startY) thanks to pred. 
	for (int i = numberOfSteps; i>0; i--)
	{
	        int movementX = pred[currentX][2*currentY];
		int movementY = pred[currentX][2*currentY+1];
		optPath[2 * i - 1] = movementX;
		optPath[2 * i] = movementY;
		currentX = currentX - movementX;
		currentY = currentY - movementY;
	}
	path = optPath;
}

void IntelligentMonster::optimalPath(int* &path, int startX, int startY, int destX, int destY, int width, int height, bool** trav, bool diagMovement)
{
        int numberOfDirs = (diagMovement ? 8 : 4);
	//The number of directions the monster can potentially  move in from any block (8 if we allow diagonal movement, 4 if we don't).
	int dirs[16] = {0,-1,1,0,0,1,-1,0,1,-1,1,1,-1,1,-1,-1};
	//dirs is an array representing the different directions the monster can move in. For each i < numberOfDirs, a direction is represented by its relative movement along the x axis in dir[2*i] and along its y axis in dir[2*i+1]. The first four movements represented are North, East, South and West, and the last four are the diagonal movements. Therefore, if numberOfDirs is 4, the diagonal movements won't be considered.

	int** pred = new int* [width];

	for (int i = 0; i < width; i++)
	{
	        pred[i] = new int [2*height];
	}
	// For a block (x,y), if (pred[x}[2*y],pred[x][2*y+1]) has been defined then it is the movement that was used to get to (x,y) from its predecessor in an optimal path from (startX,startY) to (x,y). The predecessor of (x,y) in this optimal path from (startX,startY) to (x,y) is therefore (x-pred[x}[2*y],y-pred[x][2*y+1]). This array will be used to construct an optimal path when the destination is reached.

	bool** discovered = new bool* [width];

	for (int i = 0; i < width; i++)
	{
	        discovered[i] = new bool [height];
		for (int j = 0; j < height; j++)
		{
		        discovered[i][j] = false;
		}
	}
	discovered[startX][startY] = true;
	// For a block (x,y), discovered[x][y] tells us whether the algorithm has discovered block (x,y) yet or not.
	
	priority_queue <int*, vector<int*>, queueCompare> openSet;
	// openSet contains the blocks that the algorithm is still considering as well as there expected cost. Each of it selements is an array of integers of size 3, where the first element is the expected cost (which is the number of steps of the algorithm to reach (x,y) plus h(x,y)), the second is the x coordinate, and the third is the y coordinate. The fuction queueCompare is defined such that the element with the smallest expected cost is popped when calling pop.
	int topush[3] = {h(diagMovement, startX, startY, destX, destY), startX, startY};
	openSet.push(topush);
	int currentStep;

	bool foundPath = false;

	while (!(openSet.empty()))
	{
		int* currentBlock = openSet.top();
		openSet.pop();
		int currentBlockX = currentBlock[1], currentBlockY = currentBlock[2];
		//cout << currentBlock[0] << endl;
		//cout << currentBlockX << " " << currentBlockY << endl;
		// We compute the number of steps that it took to get to this block: in openSet we store the number of steps plus the h of the block so we can get it by subtracting.
		currentStep = currentBlock[0] - h(diagMovement, currentBlockX, currentBlockY, destX, destY);
		if (currentBlockX == destX && currentBlockY == destY)
		{
		        reconstructPath(path, pred, currentStep, destX, destY);
			foundPath = true;
			break;
		}
		currentStep++;
		for (int i = 0; i < numberOfDirs; i++)
		{
		        // For each of the directions possible, we look at the current block's neighbour in that direction. If that block is in the room, is traversable, and hasn't yet been discovered, we have discovered a new shortest path from the starting position to this block, we therefore update pred and discovered accordingly, and add the block to the open set with the correct estimated cost.
		        int nextBlockX = currentBlockX + dirs[2*i];
			int nextBlockY = currentBlockY + dirs[2*i + 1];
			if (nextBlockX >= 0 && nextBlockX < width && nextBlockY >= 0 && nextBlockY < height && trav[nextBlockX][nextBlockY] && !discovered[nextBlockX][nextBlockY])
			{
			        discovered[nextBlockX][nextBlockY] = true;
				pred[nextBlockX][2*nextBlockY] = dirs[2*i];
				pred[nextBlockX][2*nextBlockY + 1] = dirs[2*i + 1];
				int* topush = new int [3];
				topush[0] = currentStep + h(diagMovement, nextBlockX, nextBlockY, destX, destY);
				topush[1] = nextBlockX;
				topush[2] = nextBlockY;
				openSet.push(topush);
			}
		}
	}
	// If we exit the while loop because openSet is empty, then there is no path from (startX,startY) to (destX,destY), we therefore make path the array containing only 0.
	if (!foundPath)
	{
	        int optPath[1] = {0};
	        path = optPath;
	}	  
}
