cmake_minimum_required(VERSION 2.8)

project(csvpp)

find_package(Boost COMPONENTS filesystem system REQUIRED)

file(GLOB_RECURSE src
     src/*.cpp)

add_library(csvpp SHARED ${src})

install(TARGETS csvpp LIBRARY DESTINATION lib)
install(DIRECTORY src/csv DESTINATION include)
