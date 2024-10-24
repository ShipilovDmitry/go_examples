set(SRC 
    src/platform_bridge_common.cpp
    src/platform_bridge_interop.cpp)

add_library(corendk_platform_bridge OBJECT ${SRC})
target_include_directories(corendk_platform_bridge PUBLIC ${PROJECT_SOURCE_DIR}/go_bridge/corendk/CoreBridge/include)