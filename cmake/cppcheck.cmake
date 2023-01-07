include(ProcessorCount)
ProcessorCount(CPU_CORES)
message(STATUS "Processor Count: ${CPU_CORES}")

find_program(CPPCHECK_EXE NAMES cppcheck)

if (CPPCHECK_EXE)
    if(NOT CPU_CORES EQUAL 0)
        set(CPPCHECK_FLAGS -j${CPU_CORES})
    endif()

    add_custom_target(cppcheck
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/cppcheck-build-dir"
        COMMAND ${CPPCHECK_EXE}
            --project="${CMAKE_BINARY_DIR}/compile_commands.json"
            --enable=all
            -i${CMAKE_SOURCE_DIR}/ci
            --xml --xml-version=2
            --cppcheck-build-dir="${CMAKE_BINARY_DIR}/cppcheck-build-dir"
            --output-file="${CMAKE_BINARY_DIR}/cppcheck-result.xml"
            ${CPPCHECK_FLAGS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Static code analysis using cppcheck tool"
    )
endif()
