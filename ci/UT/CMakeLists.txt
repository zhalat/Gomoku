cmake_minimum_required( VERSION 3.13 )

add_executable( ci
    # Unit test
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "GomokuBoardTest.cpp"
    "VectorUniqueTest.cpp"
    "SingleListTest.cpp"
    "VectorLightTest.cpp"
    "Threat2CaseAATest.cpp"
    "Threat2CaseATest.cpp"
    "Threat2CaseBTest.cpp"
    "Threat2CaseCTest.cpp"
    "Threat3CaseAATest.cpp"
    "Threat3CaseATest.cpp"
    "Threat3CaseBTest.cpp"
    "Threat3CaseCTest.cpp"
    "Threat4CaseAATest.cpp"
    "Threat4CaseATest.cpp"
    "Threat4CaseBTest.cpp"
    "Threat4CaseCTest.cpp"
    "ThreatWinnerTest.cpp"
    "SpotterTest.cpp"
#    "ScoreTest/ScoreTest.cpp"
#    "OpenBookTest/OpenBookTest.cpp"
#    "BoardScoreTest/BoardScoreTest.cpp"
#    "StateEvaluationTest/StateEvaluationTest.cpp"
#    "MinMaxTest/MinMaxTest.cpp"
#    "AlphaBetaTest/AlphaBetaTest.cpp"
    
    # Unit under test
    "../../src/DataContainers/Graph.cpp"
    "../../src/GomokuBoard.cpp"
    "../../src/Threats/ThreatFinder.cpp"
    "../../src/Threats/Threat2CaseAA.cpp"
    "../../src/Threats/Threat2CaseA.cpp"
    "../../src/Threats/Threat2CaseB.cpp"
    "../../src/Threats/Threat2CaseC.cpp"
    "../../src/Threats/Threat3CaseAA.cpp"
    "../../src/Threats/Threat3CaseA.cpp"
    "../../src/Threats/Threat3CaseB.cpp"
    "../../src/Threats/Threat3CaseC.cpp"
    "../../src/Threats/Threat4CaseAA.cpp"
    "../../src/Threats/Threat4CaseA.cpp"
    "../../src/Threats/Threat4CaseB.cpp"
    "../../src/Threats/Threat4CaseC.cpp"
    "../../src/Threats/ThreatWinner.cpp"
    "../../src/Score.cpp"
    "../../src/Spotter.cpp"

    # Stubs
 )

target_include_directories(ci PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/DataContainers"
    "${PROJECT_SOURCE_DIR}/src/Interfaces"
    "${PROJECT_SOURCE_DIR}/src/Headers/SearchAlgorithms"
    "${PROJECT_SOURCE_DIR}/src/Headers/Threats"
 )

target_link_libraries( ci PRIVATE
                       ${GTEST_LIBRARIES}
                       pthread
)
 
target_link_options(ci PRIVATE
                    -Wl,-Map,output.map
                    -Wl,--print-memory-usage
                    -Wl,--gc-sections
                    -lc
)
 