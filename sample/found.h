#ifndef _Found_H_
#define _Found_H_

#include "vector2.h"

class Found : public Precondition {
public:
    bool ExternalCondition(void *object) {
        Vector2 *point = (Vector2 *) object;

        if (point->visable == true)
            return true;
        else
            return false;
    }
};

#endif // !_Found_H_
