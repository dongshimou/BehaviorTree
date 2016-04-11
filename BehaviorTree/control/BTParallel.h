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
        BTParallel(BTBase* parentNode, Precondition* precondition = nullptr)
            : BTBase(parentNode, precondition),
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
            for(int i = 0; i < child.size(); i++)
            {
                child_status[child[i]] = running;
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
            for(int i = 0; i < child.size(); i++)
            {
                if(child_status[child[i]] == running)
                {
                    if(!child[i]->Evaluate(object))
                        return false;
                }
            }

            return true;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            for(int i = 0; i < child.size(); i++)
            {
                auto node = child[i];

                if(finish_condition == ONE)
                {
                    if(child_status[child[i]] == running)
                    {
                        child_status[child[i]] = node->Execute(object);
                    }
                    else
                    {
                        ReSetChildStatus();
                        return finish;
                    }
                }
                else
                {
                    if(child_status[child[i] ] == running)
                    {
                        child_status[child[i] ] = node->Execute(object);
                    }
                    else
                        finish_count++;
                }
            }

            if(finish_condition == ANY)
            {
                if(finish_count == child.size())
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
            for(int i = 0; i < child.size(); i++)
            {
                child_status[child[i] ] = running;
                child[i]->Transition(object);
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