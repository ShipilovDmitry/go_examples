add_library(go_bridge STATIC src/bridge.cpp)

target_include_directories(go_bridge PUBLIC ${PROJECT_SOURCE_DIR}/sources/include)