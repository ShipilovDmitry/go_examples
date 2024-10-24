# TODO
# use corendk as submodule
add_subdirectory(corendk)

add_library(go_bridge STATIC src/bridge.cpp)

target_include_directories(go_bridge PUBLIC ${PROJECT_SOURCE_DIR}/sources/include)
target_link_libraries(go_bridge PUBLIC corendk_platform_bridge)