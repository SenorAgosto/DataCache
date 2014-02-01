cmake_minimum_required(VERSION 2.8)
Project("DataCache")
include(_cmake/CompilerFlags.cmake)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(DataCache)

