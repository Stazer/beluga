cmake_minimum_required(VERSION 3.0)

project(beluga)

find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE BELUGA_SOURCE ${CMAKE_SOURCE_DIR}/source/beluga/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(beluga ${BELUGA_SOURCE})
target_link_libraries(beluga ${Boost_LIBRARIES})
