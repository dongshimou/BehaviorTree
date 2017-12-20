#ifndef _BTSelector_H_
#define _BTSelector_H_

#include "../base/BTBase.h"

namespace BehaviorTree {
    class BTPrioritySelector : public BTBase {
    public:
        BTPrioritySelector(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(debugName, parentNode, precondition, value),
                  now_index(-1),
                  last_index(-1) {
            Init();
        }

        BTPrioritySelector(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : BTBase(parentNode, precondition, value),
                  now_index(-1),
                  last_index(-1) {
            Init();
        }

        BTPrioritySelector(Precondition *precondition, int value = 0)
                : BTBase(precondition, value),
                  now_index(-1),
                  last_index(-1) {
            Init();
        }

        BTPrioritySelector(int value = 0)
                : BTBase(value),
                  now_index(-1),
                  last_index(-1) {
            Init();
        }


        virtual bool DoEvaluate(void *object) override {
            for (int i = 0; i < ChildNode.size(); i++) {
                auto node = ChildNode[i];

                if (node->Evaluate(object)) {
                    now_index = i;
                    return true;
                }
            }

            return false;
        }

        virtual RunningStatus DoExecute(void *object) override {
            RunningStatus thisFinish = STATUS_FINISH;

            if (CheckIndex(now_index)) {
                if (last_index != now_index) {
                    if (CheckIndex(last_index)) {
                        auto node = ChildNode[last_index];
                        node->Transition(object);
                    }

                    last_index = now_index;
                }
            }

            if (CheckIndex(last_index)) {
                auto node = ChildNode[last_index];
                thisFinish = node->Execute(object);

                if (thisFinish >= STATUS_FINISH) {
                    last_index = -1;
                }
            }

            return thisFinish;
        }

        virtual void DoTransition(void *object) override {
            if (CheckIndex(last_index)) {
                auto node = ChildNode[last_index];
                node->Transition(object);
            }

            last_index = -1;
        }

    protected:
        int now_index;
        int last_index;
    };

    typedef BTPrioritySelector BTSelector;

    class BTNormolSelector : public BTPrioritySelector {
        virtual bool DoEvaluate(void *object) override {
            if (CheckIndex(now_index)) {
                auto node = ChildNode[now_index];

                if (node->Evaluate(object)) {
                    return true;
                }
            }

            return false;
        }
    };
}

#endif // !_BTSelector_H_