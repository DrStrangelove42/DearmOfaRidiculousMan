#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{
protected:
	Room rooms[];
public:
	Map();
	Map(string file);
};

#endif
