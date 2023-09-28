cmake_minimum_required( VERSION 3.13 )

add_executable( ci
    # Unit test
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "GomokuBoardTest.cpp"
# "VectorUniqueTest/VectorUniqueTest.cpp"
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
    
    # Unit under test

    "../../src/DataContainers/Graph.cpp"
    "../../src/DataContainers/GraphIterator.cpp"
    "../../src/GomokuBoard.cpp"
    "../../src/BoardIterator.cpp"
    # Stubs
 )

target_include_directories(ci PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/DataContainers"
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
 