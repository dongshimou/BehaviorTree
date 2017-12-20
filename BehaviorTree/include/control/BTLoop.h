#ifndef _BTLoop_H_
#define _BTLoop_H_

#include "../base/BTBase.h"

namespace BehaviorTree {
    class BTLoop : public BTBase {
    public:
        BTLoop(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(debugName, parentNode, precondition, value),
                  loop_limit(LoopInfinite),
                  loop_count(0),
                  loop_index(0) {
            Init();
        }

        BTLoop(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(parentNode, precondition, value),
                  loop_limit(LoopInfinite),
                  loop_count(0),
                  loop_index(0) {
            Init();
        }

        BTLoop(Precondition *precondition, int value = 0)
                : BTBase(precondition, value),
                  loop_limit(LoopInfinite),
                  loop_count(0),
                  loop_index(0) {
            Init();
        }

        BTLoop(int value = 0)
                : BTBase(value),
                  loop_limit(LoopInfinite),
                  loop_count(0),
                  loop_index(0) {
            Init();
        }

        void SetLoopLimit(int limit) {
            loop_limit = limit;
        }

        void SetLoopCount(int count) {
            loop_count = count;
        }

        void SetLoopIndex(int index) {
            if (checkIndex(index)) {
                loop_index = index;
            }
        }


        virtual bool DoEvaluate(void *object) override {
            if (loop_limit != LoopInfinite && loop_count >= loop_limit) {
                return false;
            }

            if (checkIndex(loop_index)) {
                auto node = ChildNodes[loop_index];

                if (node->Evaluate(object)) {
                    return true;
                }
            }

            return false;
        }

        virtual RunningStatus DoExecute(void *object) override {
            RunningStatus thisfinish = STATUS_FINISH;

            if (checkIndex(loop_index)) {
                auto node = ChildNodes[loop_index];
                thisfinish = node->Execute(object);

                if (thisfinish == STATUS_FINISH) {
                    if (loop_limit == LoopInfinite)
                        thisfinish = STATUS_RUNNING;
                    else {
                        if (loop_count < loop_limit)
                            thisfinish = STATUS_RUNNING;
                        else
                            thisfinish = STATUS_FINISH;

                        loop_count++;
                    }
                }
            }

            if (thisfinish >= STATUS_FINISH) {
                loop_count = 0;
            }

            return thisfinish;
        }

        virtual void DoTransition(void *object) override {
            if (checkIndex(loop_index)) {
                auto node = ChildNodes[loop_index];
                node->Transition(object);
            }

            loop_count = 0;
        }

    protected:
        int loop_limit;
        int loop_count;
        int loop_index;
        static const int LoopInfinite = -1;
    };
}

#endif // !_BTLoop_H_