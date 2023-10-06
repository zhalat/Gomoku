cmake_minimum_required( VERSION 3.13 )

add_executable( gomoku-al 
    main.cpp
    DataContainers/Graph.cpp
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