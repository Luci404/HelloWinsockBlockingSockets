cmake_minimum_required(VERSION 3.10)

# HWBS
project(HWBS)

file(GLOB_RECURSE HWBS_HEADERS "${CMAKE_SOURCE_DIR}/HWBS/Source/*.h")
file(GLOB_RECURSE HWBS_SOURCES "${CMAKE_SOURCE_DIR}/HWBS/Source/*.cpp")
add_library(HWBS STATIC "${HWBS_HEADERS}" "${HWBS_SOURCES}")

set_property(TARGET HWBS PROPERTY CXX_STANDARD 20)

target_include_directories(HWBS PUBLIC "${CMAKE_SOURCE_DIR}/HWBS/Source")
target_link_libraries(HWBS PUBLIC ws2_32)

# HWBSClient
project(HWBSClient)

file(GLOB_RECURSE HWBS_CLIENT_HEADERS "${CMAKE_SOURCE_DIR}/HWBSClient/Source/*.h")
file(GLOB_RECURSE HWBS_CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/HWBSClient/Source/*.cpp")
add_executable(HWBSClient "${HWBS_CLIENT_HEADERS}" "${HWBS_CLIENT_SOURCES}")

set_property(TARGET HWBSClient PROPERTY CXX_STANDARD 20)

target_include_directories(HWBSClient PUBLIC "${CMAKE_SOURCE_DIR}/HWBSClient/Source")
target_link_libraries(HWBSClient HWBS)

# HWBSServer
project(HWBSServer)

file(GLOB_RECURSE HWBS_SERVER_HEADERS "${CMAKE_SOURCE_DIR}/HWBSServer/Source/*.h")
file(GLOB_RECURSE HWBS_SERVER_SOURCES "${CMAKE_SOURCE_DIR}/HWBSServer/Source/*.cpp")
add_executable(HWBSServer "${HWBS_SERVER_HEADERS}" "${HWBS_SERVER_SOURCES}")

set_property(TARGET HWBSServer PROPERTY CXX_STANDARD 20)

target_include_directories(HWBSServer PUBLIC "${CMAKE_SOURCE_DIR}/HWBSServer/Source")
target_link_libraries(HWBSServer HWBS)