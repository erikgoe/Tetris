cmake_minimum_required (VERSION 3.5)

# add files
set(INCLUDE_DIR ../include/${PROJECT_NAME}/)
add_executable(${PROJECT_NAME}
    main.cpp
    Board.cpp
    Figure.cpp
    Game.cpp
    Tone.cpp
    Melodies.cpp
    Text.cpp
)

# includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# linking
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-audio
    GL
)

# cotire speedup
#set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "../include/stdafx.h")
#cotire(${PROJECT_NAME})

# add tests
#add_subdirectory(tests)
