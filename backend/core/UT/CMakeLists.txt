cmake_minimum_required( VERSION 3.13 )

get_target_property(gomokuAlgo_SRC_PATH gomokuAlgo SOURCE_DIR)
get_target_property(gomokuAlgo_INCLUDE_DIR gomokuAlgo INTERFACE_INCLUDE_DIRECTORIES)

add_executable( ut
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
    "ThreatTrackerTest.cpp"
    "EvalBoardTest.cpp"
    "AlphaBetaTest.cpp"
    "OpenBookTest.cpp"

    # Stubs
 )

target_include_directories(ut PRIVATE
    "${gomokuAlgo_INCLUDE_DIR}"
 )

target_link_libraries( ut PRIVATE
                       ${GTEST_LIBRARIES}
                       gomokuAlgo
                       pthread
)

target_link_options(ut PRIVATE
                    -Wl,-Map,output.map
                    -Wl,--print-memory-usage
                    -Wl,--gc-sections
                    -lc
)
