#ifndef _found_H_
#define _found_H_
#include "monster.h"
class Found: public Precondition
{
public:
    bool ExternalCondition(void* object)
    {
        Vector2 *point = (Vector2*)object;

        if(point->visable == true)
            return true;
        else
            return false;
    }
};
#endif // !_found_H_
