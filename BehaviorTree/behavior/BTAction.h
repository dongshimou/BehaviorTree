#ifndef _BTAction_H_
#define _BTAction_H_

#include "../base/BTBase.h"

namespace BehaviorTree {
    class BTAction : public BTBase {
    public:
        BTAction(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(debugName, parentNode, precondition, value),
                  status(STATUS_READY),
                  is_finish(true) {
            Init();
        }

        BTAction(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(parentNode, precondition, value),
                  status(STATUS_READY),
                  is_finish(true) {
            Init();
        }

        BTAction(Precondition *precondition, int value = 0)
                : BTBase(precondition, value),
                  status(STATUS_READY),
                  is_finish(true) {
            Init();
        }

        BTAction(int value = 0)
                : BTBase(value),
                  status(STATUS_READY),
                  is_finish(true) {
            Init();
        }

        virtual void OnEnter(void *object) {
        }

        virtual RunningStatus Update(void *object) {
            return STATUS_FINISH;
        }

        virtual void OnExit(void *object) {
        }

        virtual bool DoEvaluate(void *object) override {
            return true;
        }

        virtual RunningStatus DoExecute(void *object) override {
            RunningStatus thisfinish = STATUS_FINISH;

            if (status == STATUS_READY) {
                OnEnter(object);
                is_finish = false;
                status = STATUS_RUNNING;
            }

            if (status == STATUS_RUNNING) {
                thisfinish = Update(object);

                if (thisfinish >= STATUS_FINISH || thisfinish == STATUS_ERROR) {
                    status = thisfinish;
                }
            }

            if (status >= STATUS_FINISH) {
                is_finish = true;
                status = STATUS_READY;
                OnExit(object);
            }

            return thisfinish;
        }

        virtual void DoTransition(void *object) override {
            if (!is_finish)
                OnExit(object);

            status = STATUS_READY;
            is_finish = true;
        }

    protected:
        RunningStatus status;
        bool is_finish;
    };
}

#endif // !_BTAction_H_