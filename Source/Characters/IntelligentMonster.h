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

class IntelligentMonster : public Monster
{
private:
        int h(bool diagMovement, int x, int y, int destX, int destY);
	void reconstructPath(int* &path, int** pred, int numberOfSteps, int destX, int destY);
	struct queueCompare
	{
	        bool operator()(const int* args1, const int* args2)
	        {
		        return args1[0] > args2[0];
		}
	};
	void optimalPath(int* &path, int startX, int startY, int destX, int destY, int width, int height, bool** trav, bool diagMovement = true);
};
#endif
