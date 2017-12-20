#ifndef _BTParallel_H_
#define _BTParallel_H_

#include "../base/BTBase.h"
#include <map>

namespace BehaviorTree {
    enum ParallelCondition {
        ONE = 1,
        ANY,
        COUNT,
        ALL,
    };

    class BTParallel : public BTBase {
    public:
        BTParallel(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(debugName, parentNode, precondition, value),
                  finish_condition(ONE),
                  finish_limit(-1) {
            ReSetChildStatus();
            Init();
        }

        BTParallel(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(parentNode, precondition, value),
                  finish_condition(ONE),
                  finish_limit(-1) {
            ReSetChildStatus();
            Init();
        }

        BTParallel(Precondition *precondition, int value = 0)
                : BTBase(precondition, value),
                  finish_condition(ONE),
                  finish_limit(-1) {
            ReSetChildStatus();
            Init();
        }

        BTParallel(int value = 0)
                : BTBase(value),
                  finish_condition(ONE),
                  finish_limit(-1) {
            ReSetChildStatus();
            Init();
        }

        int GetFinishChild() {
            return finish_count;
        }

        void ReSetChildStatus() {
            for (int i = 0; i < ChildNodes.size(); i++) {
                child_status[ChildNodes[i]] = STATUS_RUNNING;
            }

            finish_count = 0;
        }

        void SetFinishLimit(int count) {
            if (finish_condition == COUNT) {
                finish_limit = count;
            }
        }


        virtual bool DoEvaluate(void *object) override {
            for (int i = 0; i < ChildNodes.size(); i++) {
                if (child_status[ChildNodes[i]] == STATUS_RUNNING) {
                    if (!ChildNodes[i]->Evaluate(object))
                        return false;
                }
            }

            return true;
        }

        virtual RunningStatus DoExecute(void *object) override {
            for (int i = 0; i < ChildNodes.size(); i++) {
                auto node = ChildNodes[i];

                if (finish_condition == ONE) {
                    if (child_status[ChildNodes[i]] == STATUS_RUNNING) {
                        child_status[ChildNodes[i]] = node->Execute(object);
                    } else {
                        ReSetChildStatus();
                        return STATUS_FINISH;
                    }
                } else {
                    if (child_status[ChildNodes[i]] == STATUS_RUNNING) {
                        child_status[ChildNodes[i]] = node->Execute(object);
                    } else
                        finish_count++;
                }
            }

            if (finish_condition == ANY) {
                if (finish_count == ChildNodes.size()) {
                    ReSetChildStatus();
                    return STATUS_FINISH;
                } else
                    return STATUS_RUNNING;
            } else if (finish_condition == COUNT) {
                if (finish_count < finish_limit) {
                    return STATUS_RUNNING;
                } else {
                    ReSetChildStatus();
                    return STATUS_FINISH;
                }
            } else if (finish_condition == ALL) {
                if (finish_count > 0) {
                    ReSetChildStatus();
                    return STATUS_FINISH;
                } else
                    return STATUS_RUNNING;
            }
        }

        virtual void DoTransition(void *object) override {
            for (int i = 0; i < ChildNodes.size(); i++) {
                child_status[ChildNodes[i]] = STATUS_RUNNING;
                ChildNodes[i]->Transition(object);
            }
        }

    protected:
        ParallelCondition finish_condition;
        int finish_limit;
        int finish_count;
        std::map<BTBase *, RunningStatus> child_status;
    };
}

#endif // !_BTParallel_H_