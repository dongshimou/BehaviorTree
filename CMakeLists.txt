cmake_minimum_required(VERSION 3.9)
project(BehaviorTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(sample
        BehaviorTree/include/base/BTBase.h
        BehaviorTree/include/behavior/BTAction.h
        BehaviorTree/include/control/BTLoop.h
        BehaviorTree/include/control/BTParallel.h
        BehaviorTree/include/control/BTSelector.h
        BehaviorTree/include/control/BTSequence.h
        BehaviorTree/include/BehaviorTree.h

        BehaviorTree/src/base/BTBase.cpp
        BehaviorTree/src/behavior/BTAction.cpp
        BehaviorTree/src/control/BTLoop.cpp
        BehaviorTree/src/control/BTParallel.cpp
        BehaviorTree/src/control/BTSelector.cpp
        BehaviorTree/src/control/BTSequence.cpp

        sample/main.cpp
        sample/arrive.h
        sample/attack.h
        sample/found.h
        sample/idle.h
        sample/monster.h
        sample/move.h
        sample/move.h
        sample/vector2.h

        )
