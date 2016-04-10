#ifndef _BTsequence_H_
#define _BTsequence_H_

#include "BTbase.h"
namespace BehaviorTree
{
    class BTsequence: public BTbase
    {
    public:
        BTsequence(BTbase* parentNode, Precondition* precondition = nullptr)
            : BTbase(parentNode, precondition),
              now_index(-1)
        {
            Init();
        }

        virtual void Init() {}
        virtual bool DoEvaluate(void* object)
        {
            int tempNode;
            now_index == -1 ? tempNode = 0 : tempNode = now_index;

            if(CheckIndex(tempNode))
            {
                auto node = child[tempNode];

                if(node->Evaluate(object))
                {
                    return true;
                }
            }

            return false;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            RunningStatus thisFinish = finish;

            if(now_index == -1)
            {
                now_index = 0;
            }

            auto node = child[now_index];
            thisFinish = node->Execute(object);

            if(thisFinish == success)
            {
                now_index++;
                now_index == child.size() ? now_index = -1 : thisFinish = running;
            }

            if(thisFinish == error)
                now_index = -1;

            return thisFinish;
        }
        virtual void DoTransition(void* object)
        {
            if(CheckIndex(now_index))
            {
                auto node = child[now_index];
                node->Transition(object);
            }

            now_index = -1;
        }

    protected:
        int now_index;
    };
}
#endif // !_BTsequence_H_