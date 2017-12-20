#include "move.h"
#include "idle.h"
#include "attack.h"
#include "arrive.h"
#include "found.h"
#include "vector2.h"

class Monster {
public:
    void Live() {
        auto root = new BTBase;
        auto loop = new BTLoop;
        root->AddChild(loop);
        auto selector = new BTSelector;
        loop->AddChild(selector);

        auto sequence = new BTSequence;
        selector->AddChild(sequence);

        //行动
        auto m_move = new Move;
        auto m_attack = new Attack;
        auto m_idle = new Idle;

        //条件
        auto m_arrive = new Arrive;
        auto m_found = new Found;

        m_attack->setPrecondition(m_arrive);
        m_move->setPrecondition(m_found);

        selector->AddChild(m_idle);
        sequence->AddChild(m_move);
        sequence->AddChild(m_attack);

        auto point = StartPoint;
        while (true) {
            if (loop->Evaluate((void *) &point))
                loop->Execute((void *) &point);
            else
                break;
        }
        delete root;
    }
};