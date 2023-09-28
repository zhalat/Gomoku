cmake_minimum_required( VERSION 3.13 )

add_executable( gomoku-al 
    main.cpp
    DataContainers/Graph.cpp
    DataContainers/GraphIterator.cpp
    GomokuBoard.cpp
    BoardIterator.cpp
)
                
target_include_directories(gomoku-al PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/DataContainers"
)

target_link_options(gomoku-al PRIVATE
    -Wl,-Map,output.map
    -Wl,--print-memory-usage
    -Wl,--gc-sections
    -lc
)