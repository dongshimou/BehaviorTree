#ifndef _attack_H_
#define _attack_H_
#include "monster.h"
class Attack : public BTaction
{
public:
    Attack(BTbase* parent):
        BTaction(parent)
    {
    }
    bool OnEnter(void* object)
    {
        cout << "Start Attack" << endl;
        return true;
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
#endif // !_attack_H_

