cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(track-filter)
set(CMAKE_CXX_STANDARD 23)

option(BUILD_GO_BRIDGE "Build Go bridge" ON)

add_subdirectory(sources)

if (BUILD_GO_BRIDGE)
    add_subdirectory(go_bridge)
endif()