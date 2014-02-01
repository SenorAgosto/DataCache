file(GLOB test_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp *.c *.cpp)
source_group("Testing" FILES ${test_files})

add_library(DataCacheTesting ${test_files})

