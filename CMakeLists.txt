cmake_minimum_required(VERSION 3.9)
project(BehaviorTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(sample
        BehaviorTree/base/BTBase.h
        BehaviorTree/behavior/BTAction.h
        BehaviorTree/control/BTLoop.h
        BehaviorTree/control/BTParallel.h
        BehaviorTree/control/BTSelector.h
        BehaviorTree/control/BTSequence.h
        BehaviorTree/BehaviorTree.h

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
