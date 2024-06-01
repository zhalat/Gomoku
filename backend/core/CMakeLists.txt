cmake_minimum_required( VERSION 3.13 )

#for gtest_prod.h
find_package(GTest REQUIRED)

add_library( gomokuAlgo STATIC
        src/Threats/Threat2CaseA.cpp
        src/Threats/Threat2CaseAA.cpp
        src/Threats/Threat2CaseB.cpp
        src/Threats/Threat2CaseC.cpp
        src/Threats/Threat3CaseA.cpp
        src/Threats/Threat3CaseAA.cpp
        src/Threats/Threat3CaseB.cpp
        src/Threats/Threat3CaseC.cpp
        src/Threats/Threat4CaseA.cpp
        src/Threats/Threat4CaseAA.cpp
        src/Threats/Threat4CaseB.cpp
        src/Threats/Threat4CaseC.cpp
        src/Threats/ThreatFinder.cpp
        src/Threats/ThreatsBloodRelation.cpp
        src/Threats/ThreatWinner.cpp
        src/Heuristics/EvalBoard.cpp
        src/Heuristics/AlphaBeta.cpp
        src/DataContainers/Graph.cpp
        src/GomokuBoard.cpp
        src/Spotter.cpp
        src/Score.cpp
        src/OpenBook.cpp
        src/GomokuGame.cpp
        src/ThreatTracker.cpp
        src/Heuristics/TreeLogger.cpp
        src/Heuristics/MinMax.cpp
)

target_include_directories(gomokuAlgo PRIVATE
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

#for gtest_prod.h
target_link_libraries(gomokuAlgo
    PRIVATE GTest::gtest
)
