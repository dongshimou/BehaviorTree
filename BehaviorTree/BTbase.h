#ifndef _BTbase_H_
#define _BTbase_H_

#include <vector>
#include <string>
namespace BehaviorTree
{
    enum RunningStatus
    {
        error = 1,
        ready,
        running,
        finish,
        failure,
        success,
    };
    class Precondition
    {
    public:
        virtual bool ExternalCondition(void* object) = 0;
    };
    class BTbase
    {
    protected:
        std::vector<BTbase*>child;
        BTbase* parent_node;

        Precondition* node_precondition;
        std::string debug_name;
    public:
        BTbase():
            debug_name("unnamed"),
            parent_node(nullptr)
        {
            Init();
        }
        BTbase(BTbase* parentNode, Precondition* precondition = nullptr):
            debug_name("unnamed"),
            parent_node(parentNode),
            node_precondition(precondition)
        {
            Init();
        }
        virtual ~BTbase()
        {
            child.clear();
            delete node_precondition;
            node_precondition = nullptr;
        }

        virtual void Init() {}
        virtual bool DoEvaluate(void* object)
        {
            return true;
        }
        virtual RunningStatus DoExecute(void* object)
        {
            return finish;
        }
        virtual void DoTransition(void* object)
        {
        }

        virtual bool Evaluate(void* object)
        {
            return (node_precondition == nullptr || node_precondition->ExternalCondition(object)) && DoEvaluate(object);
        }
        virtual RunningStatus Execute(void* object)
        {
            return DoExecute(object);
        }
        virtual void Transition(void* object)
        {
            DoTransition(object);
        }


        BTbase& AddChild(BTbase *childNode)
        {
            child.push_back(childNode);
            return *this;
        }
        BTbase& SetPrecondition(Precondition* nodePrecondition)
        {
            if(nodePrecondition != node_precondition)
            {
                if(node_precondition != nullptr)
                    delete node_precondition;

                node_precondition = nodePrecondition;
            }

            return *this;
        }
        BTbase& SetDebugName(const char* debugName)
        {
            debug_name = debugName;
            return *this;
        }
        const char* GetDebugName()
        {
            return debug_name.c_str();
        }
        bool CheckIndex(int index)
        {
            if(index >= 0 || index < child.size())
                return true;
            else
                return false;
        }

    };
}
#endif // !_BTbase_H_