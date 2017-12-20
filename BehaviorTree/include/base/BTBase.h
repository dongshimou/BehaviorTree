#ifndef _BTBase_H_
#define _BTBase_H_

#include <vector>
#include <string>
#include <algorithm>

namespace BehaviorTree {

    template<typename T, typename... Args>
    T *new_impl(T *node, Args... args) {
        node = new T{
                args...
        };
        return node;
    };

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
        std::vector<BTBase *> ChildNodes;
    private:
        struct Private;
        Private *impl;
    public:
        explicit BTBase(
                std::string debugName,
                BTBase *parentNode = nullptr,
                Precondition *precondition = nullptr,
                int value = 0
        );

        explicit BTBase(
                BTBase *parentNode,
                Precondition *precondition = nullptr,
                int value = 0
        );

        explicit BTBase(Precondition *precondition, int value = 0);

        BTBase(int value = 0);

        BTBase(const BTBase &) = delete;

        BTBase &operator=(const BTBase &)= delete;

        BTBase(BTBase &&) = default;

        BTBase &operator=(BTBase &&)= default;

        virtual ~BTBase();

    protected:

        bool checkIndex(int index) {
            return (index >= 0 || index < ChildNodes.size());
        }

    public:

        BTBase &setParent(BTBase *parent)noexcept;

        BTBase *getParent() const noexcept;

        Precondition *getPrecondition() const noexcept;

        BTBase &AddChild(BTBase *childNode)noexcept;

        BTBase &setPrecondition(Precondition *nodePrecondition)noexcept;

        BTBase &setName(const char *debugName) noexcept;

        BTBase &setName(std::string debugName) noexcept;

        std::string getName()noexcept;

        bool Evaluate(void *object);

        RunningStatus Execute(void *object);

        void Transition(void *object);

    public:
        virtual void Init() {}

        virtual void Sort() {}

        virtual bool DoEvaluate(void *object) {
            return true;
        }

        virtual RunningStatus DoExecute(void *object) {
            return STATUS_FINISH;
        }

        virtual void DoTransition(void *object) {
        }


    };
}

#endif // !_BTBase_H_