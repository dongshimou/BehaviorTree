#ifndef _move_H_
#define _move_H_
#include "monster.h"
class Move : public BTaction
{
public:
    Move(BTbase* node)
        : BTaction(node)
    {
    }

    void OnEnter(void* object)
    {
        speed = 10;
        cout << "Move Start" << endl;
    }

    RunningStatus Update(void* object)
    {
        Vector2 *point = (Vector2*) object;
        float xx = FinishPoint.x - point->x;
        float yy = FinishPoint.y - point->y;
        float lenth = sqrt(xx * xx + yy * yy);
        float every = speed / lenth;
        float dx = FinishPoint.x - point->x;
        float dy = FinishPoint.y - point->y;

        if(sqrt(dx * dx + dy * dy) <= speed)
        {
            return success;
        }
        else
        {
            point->x += xx * every ;
            point->y += yy * every ;
            cout << "Moving" << point->x << " " << point->y << endl;
            return running;
        }
    }

    void OnExit(void* object)
    {
        cout << "Move success" << endl;
    }
private:
    float speed;
};
#endif // !_move_H_