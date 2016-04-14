#ifndef _BTSequence_H_
#define _BTSequence_H_

#include "base/BTBase.h"
namespace BehaviorTree
{
    class BTSequence: public BTBase
    {
    public:
        BTSequence(std::string debugName, BTBase* parentNode = nullptr, Precondition* precondition = nullptr, int value = 0)
            : BTBase(debugName, parentNode, precondition, value),
              now_index(-1)
        {
            Init();
        }
        BTSequence(BTBase* parentNode , Precondition* precondition = nullptr, int value = 0)
            : BTBase(parentNode, precondition, value),
              now_index(-1)
        {
            Init();
        }
        BTSequence(Precondition* preconditon, int value = 0)
            : BTBase(preconditon, value),
              now_index(-1)
        {
            Init();
        }
        BTSequence(int value = 0)
            : BTBase(value),
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
                auto node = ChildNode[tempNode];

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

            auto node = ChildNode[now_index];
            thisFinish = node->Execute(object);

            if(thisFinish == success)
            {
                now_index++;
                now_index == ChildNode.size() ? now_index = -1 : thisFinish = running;
            }

            if(thisFinish == error)
                now_index = -1;

            return thisFinish;
        }
        virtual void DoTransition(void* object)
        {
            if(CheckIndex(now_index))
            {
                auto node = ChildNode[now_index];
                node->Transition(object);
            }

            now_index = -1;
        }

    protected:
        int now_index;
    };

    class BTAndSequence: public BTSequence
    {
        virtual bool DoEvaluate(void* object)
        {
            int tempNode;
            now_index == -1 ? tempNode = 0 : tempNode = now_index;

            if(CheckIndex(tempNode))
            {
                auto node = ChildNode[tempNode];

                if(node->Evaluate(object))
                {
                    return true;
                }
            }

            Transition(object);
            return false;
        }
    };
}

#endif // !_BTSequence_H_