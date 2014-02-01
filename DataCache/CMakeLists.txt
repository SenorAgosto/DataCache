file( GLOB interface_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp)
file( GLOB implementation_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Source/*.h Source/*.hpp Source/*.c Source/*.cpp)

source_group("Source" FILES ${implementation_files})
source_group("Interface" FILES ${interface_files})

add_library(DataCache ${implementation_files} ${interface_files})
add_subdirectory(Testing)
add_subdirectory(UnitTest)

