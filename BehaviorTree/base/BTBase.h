#ifndef _BTBase_H_
#define _BTBase_H_

#include <vector>
#include <string>
#include <algorithm>

namespace BehaviorTree {
    enum RunningStatus {
        STATUS_ERROR = 1,
        STATUS_READY,
        STATUS_RUNNING,
        STATUS_FINISH,
        STATUS_FAILURE,
        STATUS_SUCCESS,
    };

    class Precondition {
    public:
        virtual bool ExternalCondition(void *object) = 0;
    };

    class BTBase {
    protected:
        std::vector<BTBase *> ChildNode;
        BTBase *ParentNode;
        Precondition *NodePrecondition;
        std::string DebugName;
        int Value;
    public:
        BTBase(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : DebugName(debugName),
                  ParentNode(parentNode),
                  NodePrecondition(precondition),
                  Value(value) {
            Init();
        }

        BTBase(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        )
                : DebugName("unnamed"),
                  ParentNode(parentNode),
                  NodePrecondition(precondition),
                  Value(value) {
            Init();
        }

        BTBase(Precondition *precondition, int value = 0)
                : DebugName("unnamed"),
                  ParentNode(nullptr),
                  NodePrecondition(precondition),
                  Value(value) {
            Init();
        }

        BTBase(int value = 0)
                : DebugName("unnamed"),
                  ParentNode(nullptr),
                  NodePrecondition(nullptr),
                  Value(value) {
            Init();
        }

        BTBase(const BTBase &) = delete;

        BTBase &operator=(const BTBase &)= delete;

        BTBase(BTBase &&) = default;

        BTBase &operator=(BTBase &&)= default;

        virtual ~BTBase() {
            for (auto i : ChildNode) {
                delete i;
                i = nullptr;
            }

            ChildNode.clear();
            delete NodePrecondition;
            NodePrecondition = nullptr;
        }

    protected:
        static bool BTBaseCompare(BTBase *a, BTBase *b) {
            return a->Value > b->Value;
        }

        bool CheckIndex(int index) {
            if (index >= 0 || index < ChildNode.size())
                return true;
            else
                return false;
        }

    public:
        virtual void Init() {}

        virtual void Sort() {
            std::sort(ChildNode.begin(), ChildNode.end(), BTBaseCompare);
        }

        virtual bool DoEvaluate(void *object) {
            return true;
        }

        virtual RunningStatus DoExecute(void *object) {
            return STATUS_FINISH;
        }

        virtual void DoTransition(void *object) {
        }

        virtual bool Evaluate(void *object) {
            return (NodePrecondition == nullptr || NodePrecondition->ExternalCondition(object)) && DoEvaluate(object);
        }

        virtual RunningStatus Execute(void *object) {
            return DoExecute(object);
        }

        virtual void Transition(void *object) {
            DoTransition(object);
        }

        BTBase &AddChild(BTBase *childNode) {
            childNode->ParentNode = this;
            ChildNode.push_back(childNode);
            return *this;
        }

        BTBase &SetPrecondition(Precondition *nodePrecondition) {
            if (nodePrecondition != NodePrecondition) {
                if (NodePrecondition != nullptr)
                    delete NodePrecondition;

                NodePrecondition = nodePrecondition;
            }

            return *this;
        }

        BTBase &SetDebugName(const char *debugName) {
            DebugName = debugName;
            return *this;
        }

        BTBase &SetDebugName(std::string debugName) {
            DebugName = debugName;
            return *this;
        }

        const char *GetDebugName() {
            return DebugName.c_str();
        }
    };
}

#endif // !_BTBase_H_