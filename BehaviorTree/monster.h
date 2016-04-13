#include "move.h"
#include "idle.h"
#include "attack.h"
#include "arrive.h"
#include "found.h"
#include "vector2.h"

class Monster
{
private:
    Vector2 *point;
public:
    Monster(int xx = 0, int yy = 0, bool v = true)
        : point(new Vector2(xx, yy, v))
    {
    }
    void Live()
    {
        auto root = new BTBase();
        auto loop = new BTLoop(root);
        root->AddChild(loop);
        auto selector = new BTSelector(loop);
        loop->AddChild(selector);
        auto sequence = new BTSequence(selector);
        selector->AddChild(sequence);
        auto m_move = new Move(sequence);
        auto m_attack = new Attack(sequence);
        auto m_arrive = new Arrive();
        auto m_found = new Found();
        auto m_idle = new Idle(selector);
        selector->AddChild(m_idle);
        m_attack->SetPrecondition(m_arrive);
        m_move->SetPrecondition(m_found);
        sequence->AddChild(m_move);
        sequence->AddChild(m_attack);
        point = new Vector2(StartPoint);
        //point->visable = false;

        while(true)
        {
            if(loop->Evaluate((void*)point))
                loop->Execute((void*)point);

            getchar();
        }
    }
};