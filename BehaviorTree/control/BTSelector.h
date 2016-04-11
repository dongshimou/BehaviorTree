#ifndef _BTSelector_H_
#define _BTSelector_H_

#include "base/BTBase.h"
namespace BehaviorTree
{
    class BTSelector: public BTBase
    {
    public:
        BTSelector(BTBase* parentNode, Precondition* precondition = nullptr)
            : BTBase(parentNode, precondition),
              now_index(-1),
              last_index(-1)
        {
            Init();
        }

        virtual void Init() {}
        virtual bool DoEvaluate(void* object)
        {
            for(int i = 0; i < child.size(); i++)
            {
                auto node = child[i];

                if(node->Evaluate(object))
                {
                    now_index = i;
                    return true;
                }
            }

            return false;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            RunningStatus thisFinish = finish;

            if(CheckIndex(now_index))
            {
                if(last_index != now_index)
                {
                    if(CheckIndex(last_index))
                    {
                        auto node = child[last_index];
                        node->DoTransition(object);
                    }

                    last_index = now_index;
                }
            }

            if(CheckIndex(last_index))
            {
                auto node = child[last_index];
                thisFinish = node->Execute(object);

                if(thisFinish >= finish)
                {
                    last_index = -1;
                }
            }

            return thisFinish;
        }
        virtual void DoTransition(void* object)
        {
            if(CheckIndex(last_index))
            {
                auto node = child[last_index];
                node->Transition(object);
            }

            last_index = -1;
        }

    protected:
        int now_index;
        int last_index;
    };
    class BTNormolSelector: public BTSelector
    {
        virtual bool DoEvaluate(void* object)
        {
            if(CheckIndex(now_index))
            {
                auto node = child[now_index];

                if(node->Evaluate(object))
                {
                    return true;
                }
            }

            return false;
        }
    };
}

#endif // !_BTSelector_H_