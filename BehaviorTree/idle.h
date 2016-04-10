#ifndef _idle_H_
#define _idle_H_
#include "monster.h"
class Idle : public BTaction
{
public:
    Idle(BTbase* parent):
        BTaction(parent)
    {
    }

    bool OnEnter(void* object)
    {
        Vector2 *point = (Vector2*)object;

        if(point->visable == false)
        {
            cout << "no prey" << endl;
            return true;
        }
        else
            return false;
    }
    RunningStatus Update(void* object)
    {
        Vector2 *point = (Vector2*)object;
        point->x = rand() % 100;
        point->y = rand() % 100;
        cout << "i go to " << point->x << " " << point->y << endl;
        return success;
    }
    void OnExit(void* object)
    {
        cout << "stop idle" << endl;
        Vector2 *point = (Vector2*)object;
        point->visable = true;
    }
};
#endif // !_idle_H_

