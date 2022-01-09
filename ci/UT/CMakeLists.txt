cmake_minimum_required( VERSION 3.13 )

add_executable( ci 
    # Unit test
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "GraphTest/GraphTest.cpp"
    
    #"GomokuBoardTest/GomokuBoardTest.cpp"
    "VectorUniqueTest/VectorUniqueTest.cpp"
#    "SingleListTest/SingleListTest.cpp"
#    "VectorLightTest/VectorLightTest.cpp"
#    "ThreatsTests/Threat2CaseAATest/Threat2CaseAATest.cpp"
#    "ThreatsTests/Threat2CaseATest/Threat2CaseATest.cpp"
#    "ThreatsTests/Threat2CaseBTest/Threat2CaseBTest.cpp"
#    "ThreatsTests/Threat2CaseCTest/Threat2CaseCTest.cpp"
#    "ThreatsTests/Threat3CaseAATest/Threat3CaseAATest.cpp"
#    "ThreatsTests/Threat3CaseATest/Threat3CaseATest.cpp"
#    "ThreatsTests/Threat3CaseBTest/Threat3CaseBTest.cpp"
#    "ThreatsTests/Threat3CaseCTest/Threat3CaseCTest.cpp"
#    "ThreatsTests/Threat4CaseAATest/Threat4CaseAATest.cpp"
#    "ThreatsTests/Threat4CaseATest/Threat4CaseATest.cpp"
#    "ThreatsTests/Threat4CaseBTest/Threat4CaseBTest.cpp"
#    "ThreatsTests/ThreatWinnerTest/ThreatWinnerTest.cpp"
#    "SpotterTest/SpotterTest.cpp"
#    "ScoreTest/ScoreTest.cpp"
#    "OpenBookTest/OpenBookTest.cpp"
#    "BoardScoreTest/BoardScoreTest.cpp"
#    "StateEvaluationTest/StateEvaluationTest.cpp"
#    "MinMaxTest/MinMaxTest.cpp"
#    "AlphaBetaTest/AlphaBetaTest.cpp"
    
#    # Unit under test
#    "../../src/Sources/GomokuBoard.cpp"
#    "../../src/Sources/BoardScore.cpp"
#    "../../src/Sources/BoardIterator.cpp"
    "../../src/Sources/DataContainers/GraphIterator.cpp"
#    "../../src/Sources/OpenBook.cpp"
    "../../src/Sources/DataContainers/Graph.cpp"
#    "../../src/Sources/DataContainers/VectorLight.cpp"
#    "../../src/Sources/DataContainers/VectorLightIterator.cpp"
#    "../../src/Sources/GomokuBoard.cpp"
#    "../../src/Sources/Spotter.cpp"
#    "../../src/Sources/Score.cpp"
#    "../../src/Sources/Threats/ThreatFinder.cpp"
#    "../../src/Sources/Threats/ThreatWinner.cpp"
#    "../../src/Sources/Threats/Threat4CaseA.cpp"
#    "../../src/Sources/Threats/Threat4CaseAA.cpp"
#    "../../src/Sources/Threats/Threat4CaseB.cpp"
#    "../../src/Sources/Threats/Threat4CaseC.cpp"
#    "../../src/Sources/Threats/Threat3CaseA.cpp"
#    "../../src/Sources/Threats/Threat3CaseAA.cpp"
#    "../../src/Sources/Threats/Threat3CaseB.cpp"
#    "../../src/Sources/Threats/Threat3CaseC.cpp"
#    "../../src/Sources/Threats/Threat2CaseA.cpp"
#    "../../src/Sources/Threats/Threat2CaseAA.cpp"
#    "../../src/Sources/Threats/Threat2CaseB.cpp"
#    "../../src/Sources/Threats/Threat2CaseC.cpp"
#    "../../src/Sources/Threats/ThreatsBloodRelation.cpp"
#    "../../src/Sources/SearchAlgorithms/StateEvaluation.cpp"
#    "../../src/Sources/SearchAlgorithms/MinMax.cpp"
#    "../../src/Sources/SearchAlgorithms/AlphaBeta.cpp"
#    # Stubs
 )

target_include_directories(ci PUBLIC
    "${PROJECT_SOURCE_DIR}/src/Headers"
    "${PROJECT_SOURCE_DIR}/src/Headers/DataContainers"
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
 