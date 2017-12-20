//
// Created by 董施谋 on 2017/12/20.
//

#include "../../include/base/BTBase.h"

namespace BehaviorTree {

    struct BTBase::Private {
        std::string name;
        BTBase *parent;
        Precondition *pre;
        int value;
    };

    BTBase::BTBase(std::string debugName,
                   BTBase *parentNode,
                   Precondition *precondition,
                   int value) {
        impl = new_impl(impl, debugName, parentNode, precondition, value);
        Init();
    }

    BTBase::BTBase(BTBase *parentNode,
                   Precondition *precondition,
                   int value) {
        impl = new_impl(impl, std::string("unnamed"),
                        parentNode, precondition, value);
        Init();
    }

    BTBase::BTBase(Precondition *precondition, int value) {
        impl = new_impl(impl, std::string("unnamed"),
                        nullptr, precondition, value);
        Init();
    }

    BTBase::BTBase(int value) {
        impl = new_impl(impl, std::string("unnamed"),
                        nullptr, nullptr, value);
        Init();
    }

    BTBase::~BTBase() {
        for (auto i : ChildNodes) {
            delete i;
        }
        ChildNodes.clear();
        delete impl->pre;
        delete impl;
    }

    bool BTBase::Evaluate(void *object) {
        return (impl->pre == nullptr || impl->pre->ExternalCondition(object)) && DoEvaluate(object);
    }

    RunningStatus BTBase::Execute(void *object) {
        return DoExecute(object);
    }

    void BTBase::Transition(void *object) {
        DoTransition(object);
    }

    BTBase &BTBase::AddChild(BTBase *childNode) noexcept {
        childNode->setParent(this);
        ChildNodes.push_back(childNode);
        return *this;
    }

    BTBase &BTBase::setParent(BTBase *parent) noexcept {
        this->impl->parent = parent;
        return *this;
    }

    BTBase *BTBase::getParent() const noexcept {
        return impl->parent;
    }

    Precondition *BTBase::getPrecondition() const noexcept {
        return impl->pre;
    }

    BTBase &BTBase::setPrecondition(Precondition *nodePrecondition)noexcept {
        if (nodePrecondition != impl->pre) {
            if (impl->pre != nullptr)
                delete impl->pre;
            impl->pre = nodePrecondition;
        }
        return *this;
    }

    BTBase &BTBase::setName(const char *debugName) noexcept {
        return this->setName(std::string(debugName));
    }

    BTBase &BTBase::setName(std::string debugName) noexcept {
        impl->name = debugName;
        return *this;
    }

    std::string BTBase::getName() noexcept {
        return impl->name;
    }


}
