/*This map is a fixed-size map with only one room.*/
#include "Dummy.h"

DummyMap::DummyMap()
{
	DummyRoom room;
}

DummyRoom::DummyRoom()
{
	blocks = new Block[20][30];
}