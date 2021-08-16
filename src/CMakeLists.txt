cmake_minimum_required( VERSION 3.13 )

add_executable( gomoku-al 
    main.cpp
    Sources/DataContainers/Graph.cpp
    Sources/DataContainers/GraphIterator.cpp
    Sources/GomokuBoard.cpp
    Sources/BoardIterator.cpp
    Sources/Score.cpp
    Sources/Spotter.cpp
    Sources/BoardScore.cpp
    Sources/GomokuGame.cpp
    Sources/Logger.cpp
    Sources/OpenBook.cpp
    Sources/SearchAlgorithms/MinMax.cpp
    Sources/SearchAlgorithms/AlphaBeta.cpp
    Sources/SearchAlgorithms/StateEvaluation.cpp
    Sources/Threats/ThreatFinder.cpp
    Sources/Threats/Threat4CaseA.cpp
    Sources/Threats/Threat4CaseAA.cpp
    Sources/Threats/Threat4CaseB.cpp
    Sources/Threats/Threat4CaseC.cpp
    Sources/Threats/Threat3CaseA.cpp
    Sources/Threats/Threat3CaseAA.cpp
    Sources/Threats/Threat3CaseB.cpp
    Sources/Threats/Threat3CaseC.cpp
    Sources/Threats/Threat2CaseA.cpp
    Sources/Threats/Threat2CaseAA.cpp
    Sources/Threats/Threat2CaseB.cpp
    Sources/Threats/Threat2CaseC.cpp
    Sources/Threats/ThreatWinner.cpp
    Sources/Threats/ThreatsBloodRelation.cpp
)
                
target_include_directories(gomoku-al PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers"
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers/DataContainers"
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers/SearchAlgorithms"
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers/Threats"
)

target_link_options(gomoku-al PRIVATE
    -Wl,-Map,output.map
    -Wl,--print-memory-usage
    -Wl,--gc-sections
    -lc
)