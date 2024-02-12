cmake_minimum_required(VERSION 3.21)
project(yamltest)

set(CMAKE_CXX_STANDARD 17)
find_package(yaml-cpp REQUIRED)

include_directories(${YAML_CPP_INCLUDE_DIR})

add_executable(yamltest main.cpp)

target_link_libraries(yamltest yaml-cpp)
