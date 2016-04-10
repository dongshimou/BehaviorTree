#ifndef _BTaction_H_
#define _BTaction_H_

#include "BTbase.h"
namespace BehaviorTree
{
    class BTaction: public BTbase
    {
    public:
        BTaction(BTbase* parentNode, Precondition* precondition = nullptr)
            : BTbase(parentNode, precondition),
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
#endif // !_BTaction_H_