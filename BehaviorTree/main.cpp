#include "monster.h"
#include "move.h"
#include "idle.h"
#include "attack.h"
#include "arrive.h"
#include "found.h"
using namespace BehaviorTree;
using namespace std;
int main()
{
    auto root = new BTbase();
    auto loop = new BTloop(root);
    root->AddChild(loop);
    auto selector = new BTselector(loop);
    loop->AddChild(selector);
    auto sequence = new BTsequence(selector);
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
    Vector2 *temp = new Vector2(StartPoint);
    temp->visable = false;

    while(true)
    {
        if(loop->Evaluate((void*)temp))
            loop->Execute((void*)temp);

        getchar();
    }
}