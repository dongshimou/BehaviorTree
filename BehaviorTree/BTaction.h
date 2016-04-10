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
              status(ready)
        {
            Init();
        }
        virtual void Init() {}
        virtual bool OnEnter(void* object)
        {
            return true;
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
                status = ready;
                OnExit(object);
            }

            return thisfinish;
        }

        virtual void DoTransition(void* object)
        {
        }
    protected:
        RunningStatus status;
    };
}
#endif // !_BTaction_H_