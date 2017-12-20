#ifndef _Vector2_H_
#define _Vector2_H_

#include "../BehaviorTree/BehaviorTree.h"
#include <iostream>
#include <string>

#define eps 1e-6
using namespace BehaviorTree;
using namespace std;

struct Vector2 {
    float x, y;
    bool visable;

    Vector2(int xx, int yy, bool v = true)
            : x(xx), y(yy), visable(v) {}

    Vector2() {}
};

Vector2 StartPoint(20, 20);
Vector2 FinishPoint(40, 40);

#endif // !_Vector2_H_

