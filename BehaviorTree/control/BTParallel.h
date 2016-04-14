#ifndef _BTParallel_H_
#define _BTParallel_H_

#include "base/BTBase.h"
#include <map>
namespace BehaviorTree
{
    enum ParallelCondition
    {
        ONE = 1,
        ANY ,
        COUNT,
        ALL ,
    };
    class BTParallel: public BTBase
    {
    public:
        BTParallel(std::string debugName, BTBase* parentNode = nullptr, Precondition* precondition = nullptr, int value = 0)
            : BTBase(debugName, parentNode, precondition, value),
              finish_condition(ONE),
              finish_limit(-1)
        {
            ReSetChildStatus();
            Init();
        }
        BTParallel(BTBase* parentNode , Precondition* precondition = nullptr, int value = 0)
            : BTBase(parentNode, precondition, value),
              finish_condition(ONE),
              finish_limit(-1)
        {
            ReSetChildStatus();
            Init();
        }
        BTParallel(Precondition* preconditon, int value = 0)
            : BTBase(preconditon, value),
              finish_condition(ONE),
              finish_limit(-1)
        {
            ReSetChildStatus();
            Init();
        }
        BTParallel(int value = 0)
            : BTBase(value),
              finish_condition(ONE),
              finish_limit(-1)
        {
            ReSetChildStatus();
            Init();
        }
        int GetFinishChild()
        {
            return finish_count;
        }
        void ReSetChildStatus()
        {
            for(int i = 0; i < ChildNode.size(); i++)
            {
                child_status[ChildNode[i]] = running;
            }

            finish_count = 0;
        }
        void SetFinishLimit(int count)
        {
            if(finish_condition == COUNT)
            {
                finish_limit = count;
            }
        }

        virtual void Init() {}
        virtual bool DoEvaluate(void* object)
        {
            for(int i = 0; i < ChildNode.size(); i++)
            {
                if(child_status[ChildNode[i]] == running)
                {
                    if(!ChildNode[i]->Evaluate(object))
                        return false;
                }
            }

            return true;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            for(int i = 0; i < ChildNode.size(); i++)
            {
                auto node = ChildNode[i];

                if(finish_condition == ONE)
                {
                    if(child_status[ChildNode[i]] == running)
                    {
                        child_status[ChildNode[i]] = node->Execute(object);
                    }
                    else
                    {
                        ReSetChildStatus();
                        return finish;
                    }
                }
                else
                {
                    if(child_status[ChildNode[i] ] == running)
                    {
                        child_status[ChildNode[i] ] = node->Execute(object);
                    }
                    else
                        finish_count++;
                }
            }

            if(finish_condition == ANY)
            {
                if(finish_count == ChildNode.size())
                {
                    ReSetChildStatus();
                    return finish;
                }
                else
                    return running;
            }
            else if(finish_condition == COUNT)
            {
                if(finish_count < finish_limit)
                {
                    return running;
                }
                else
                {
                    ReSetChildStatus();
                    return finish;
                }
            }
            else if(finish_condition = ALL)
            {
                if(finish_count > 0)
                {
                    ReSetChildStatus();
                    return finish;
                }
                else
                    return running;
            }
        }
        virtual void DoTransition(void* object)
        {
            for(int i = 0; i < ChildNode.size(); i++)
            {
                child_status[ChildNode[i] ] = running;
                ChildNode[i]->Transition(object);
            }
        }

    protected:
        ParallelCondition finish_condition;
        int finish_limit;
        int finish_count;
        std::map<BTBase*, RunningStatus> child_status;
    };
}

#endif // !_BTParallel_H_