cmake_minimum_required(VERSION 2.8.3)
project(jaka_controller_tcp_cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## Compile as C++11
add_compile_options(-std=c++11)

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

###########
## Build ##
###########

include_directories(
 include
 /usr/include/jsoncpp
)

## Declare a C++ library
add_library(config SHARED src/libs/config.cpp)
add_library(robot_client_tcp SHARED src/libs/robot_client_tcp.cpp)

add_executable(robot_client_tcp_test src/robot_client_tcp_test.cpp)
target_link_libraries(robot_client_tcp_test config robot_client_tcp jsoncpp)
