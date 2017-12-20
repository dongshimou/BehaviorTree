//
// Created by 董施谋 on 2017/12/20.
//

#include "../../include/base/BTBase.h"

namespace BehaviorTree {

    BTBase::BTBase(
            std::string debugName,
            BTBase *parentNode,
            Precondition *precondition,
            int value
    )
            : DebugName(debugName),
              ParentNode(parentNode),
              NodePrecondition(precondition),
              Value(value) {
        Init();
    }

}
