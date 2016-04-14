#ifndef _BTAction_H_
#define _BTAction_H_

#include "base/BTBase.h"
namespace BehaviorTree
{
    class BTAction: public BTBase
    {
    public:
        BTAction(std::string debugName, BTBase* parentNode = nullptr, Precondition* precondition = nullptr, int value = 0)
            : BTBase(debugName, parentNode, precondition, value),
              status(ready),
              is_finish(true)
        {
            Init();
        }
        BTAction(BTBase* parentNode , Precondition* precondition = nullptr, int value = 0)
            : BTBase(parentNode, precondition, value),
              status(ready),
              is_finish(true)
        {
            Init();
        }
        BTAction(Precondition* preconditon, int value = 0)
            : BTBase(preconditon, value),
              status(ready),
              is_finish(true)
        {
            Init();
        }
        BTAction(int value = 0)
            : BTBase(value),
              status(ready),
              is_finish(true)
        {
            Init();
        }
        virtual void Init() {}
        virtual void OnEnter(void* object)
        {
        }
        virtual RunningStatus Update(void* object)
        {
            return finish;
        }
        virtual void OnExit(void* object)
        {
        }
        virtual bool DoEvaluate(void* object)
        {
            return true;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            RunningStatus thisfinish = finish;

            if(status == ready)
            {
                OnEnter(object);
                is_finish = false;
                status = running;
            }

            if(status == running)
            {
                thisfinish = Update(object);

                if(thisfinish >= finish || thisfinish == error)
                {
                    status = thisfinish;
                }
            }

            if(status >= finish)
            {
                is_finish = true;
                status = ready;
                OnExit(object);
            }

            return thisfinish;
        }

        virtual void DoTransition(void* object)
        {
            if(!is_finish)
                OnExit(object);

            status = ready;
            is_finish = true;
        }
    protected:
        RunningStatus status;
        bool is_finish;
    };
}

#endif // !_BTAction_H_