find_package(Python3)
if(Python3_Interpreter_FOUND)
    add_custom_target(format_sources # ALL
        COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/cmake/code_format/clang-format.py
            --path=${CMAKE_SOURCE_DIR}/src
            --clang_ignore ${CMAKE_SOURCE_DIR}/cmake/code_format/.clangignore
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Format source code using clang-format tool"
    )
endif()
