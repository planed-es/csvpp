cmake_minimum_required(VERSION 2.8)

project(csvpp)

find_package(Boost COMPONENTS filesystem system REQUIRED)

if (CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB_RECURSE src
     src/*.cpp)

add_library(csvpp SHARED ${src})
add_library(csvpp_static STATIC ${src})

target_include_directories(csvpp PUBLIC src)
target_include_directories(csvpp_static PUBLIC src)

install(TARGETS csvpp LIBRARY DESTINATION lib)
install(DIRECTORY src/csv DESTINATION include)
