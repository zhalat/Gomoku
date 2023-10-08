cmake_minimum_required( VERSION 3.13 )

add_executable( gomoku-al 
    main.cpp
    DataContainers/Graph.cpp
    Threats/Threat2CaseA.cpp
    Threats/Threat2CaseAA.cpp
    Threats/Threat2CaseB.cpp
    Threats/Threat2CaseC.cpp
    Threats/Threat3CaseA.cpp
    Threats/Threat3CaseAA.cpp
    Threats/Threat3CaseB.cpp
    Threats/Threat3CaseC.cpp
    Threats/Threat4CaseA.cpp
    Threats/Threat4CaseAA.cpp
    Threats/Threat4CaseB.cpp
    Threats/Threat4CaseC.cpp
    Threats/ThreatFinder.cpp
    Threats/ThreatsBloodRelation.cpp
    Threats/ThreatWinner.cpp
    GomokuBoard.cpp
    Exceptions.h)
                
target_include_directories(gomoku-al PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_options(gomoku-al PRIVATE
    -Wl,-Map,output.map
    -Wl,--print-memory-usage
    -Wl,--gc-sections
    -lc
)