//this file defines the acquire interaction
#ifndef ACQUIRE_H
#define ACQUIRE_H

#include <string>
// input should be number of aquired items, and the item index
// there should be a limit of the aquired items
void Charactor :: aquire (int n, int index)
{
    if(n + Current(index) < =Limit(index))
    {
        Current(index)= n + Current(index); //update number of index
    }
    else
    {
        Current(index)= Limit(index);
    }
}


#endif
