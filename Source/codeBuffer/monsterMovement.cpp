#if false
//modification in monster.h
protected:
int speed

public:
int direction, // 0,1,2,3 stands for left, right, up, down


void Monster :: randomMoving()
// in this function the Monster is Moving randomly on the map and when it meets obstacles it turns back.
{
    direction = rand()%4;
    if ( getTrav() = false )//if it didn't hit a obstacle
    {
        //todo : march towards this direction for n seconds
    }
    else 
    {
        randomMoving();// if meet obstacle reset direction
    } 
}

void Monster :: towardObject()
// in this function the Monster is alarmed and will move to the object.
{

}
#endif