#ifndef _Arrive_H_
#define _Arrive_H_

#include "vector2.h"

class Arrive : public Precondition {
public:
    bool ExternalCondition(void *object) {
        Vector2 *point = (Vector2 *) object;
        float dx = FinishPoint.x - point->x;
        float dy = FinishPoint.y - point->y;

        if (std::sqrt(dx * dx + dy * dy) <= 5)
            return true;
        else
            return false;
    }
};

#endif // !_Arrive_H_
