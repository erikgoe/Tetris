cmake_minimum_required(VERSION 3.5)

project(tetris)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")
endif()

# scripts
#include(${DEV_SOURCE_DIR}/.extlib/cotire/cotire.cmake)

# module paths

# packages
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED system window graphics)

# subdirectories
#add_subdirectory(cmake)
#add_subdirectory(config)
#add_subdirectory(doc)
#add_subdirectory(samples)
add_subdirectory(app/src/main/jni)
#add_subdirectory(tests)

# startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}_test)
