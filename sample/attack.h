#ifndef _Attack_H_
#define _Attack_H_
#include "vector2.h"
class Attack : public BTAction
{
public:
    Attack(BTBase* parent):
        BTAction(parent)
    {
    }
    void OnEnter(void* object)
    {
        cout << "Start Attack" << endl;
    }
    RunningStatus Update(void* object)
    {
        cout << "i kill it" << endl;
        Vector2 *point = (Vector2*)object;
        point->visable = false;
        return success;
    }
    void OnExit(void* object)
    {
        cout << "stop attack" << endl;
    }
};
#endif // !_Attack_H_

