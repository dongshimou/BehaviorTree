#ifndef _Move_H_
#define _Move_H_

#include "vector2.h"

#include <cmath>

class Move : public BTAction {
public:
    Move(BTBase *node= nullptr)
            : BTAction(node) {
    }

    void OnEnter(void *object) {
        Vector2 *point = (Vector2 *) object;
        speed = 10.0;
        dx = FinishPoint.x - point->x;
        dy = FinishPoint.y - point->y;
        lenth = std::sqrt(dx * dx + dy * dy);
        cout << "Move Start" << endl;
    }

    RunningStatus Update(void *object) {
        Vector2 *point = (Vector2 *) object;
        cout << "Moving" << point->x << " " << point->y << endl;
        float xx = FinishPoint.x - point->x;
        float yy = FinishPoint.y - point->y;

        if (std::sqrt(xx * xx + yy * yy) <= speed / 2) {
            point->x = FinishPoint.x;
            point->y = FinishPoint.y;
            return STATUS_SUCCESS;
        } else {
            point->x += (speed / lenth) * dx;
            point->y += (speed / lenth) * dy;
            return STATUS_RUNNING;
        }
    }

    void OnExit(void *object) {
        cout << "Move success" << endl;
    }

private:
    float speed;
    float lenth;
    float dx, dy;
};

#endif // !_Move_H_