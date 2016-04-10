#ifndef _arrive_H_
#define _arrive_H_
#include "monster.h"
class Arrive: public Precondition
{
public:
    bool ExternalCondition(void* object)
    {
        Vector2 *point = (Vector2*)object;

        if(abs(point->x - FinishPoint.x) <= 1 && abs(point->x - FinishPoint.x) <= 1)
            return true;
        else
            return false;
    }
};

#endif // !_arrive_H_
