#ifndef _BTselector_H_
#define _BTselector_H_

#include "BTbase.h"
namespace BehaviorTree
{
    class BTselector: public BTbase
    {
    public:
        BTselector(BTbase* parentNode, Precondition* precondition = nullptr)
            : BTbase(parentNode, precondition),
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
                        node->Execute(object);
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
}
#endif // !_BTselector_H_