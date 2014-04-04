file( GLOB interface_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp)
file( GLOB implementation_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Source/*.h Source/*.hpp Source/*.c Source/*.cpp)
file( GLOB details_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Details/*.h Details/*.hpp)
file( GLOB exceptions_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Exception/*.h Exception/*.hpp)

source_group("Source" FILES ${implementation_files})
source_group("Interface" FILES ${interface_files})
source_group("Interface\\Details" FILES ${details_files})
source_group("Interface\\Exception" FILES ${exceptions_files})

add_library(DataCache ${implementation_files} ${interface_files} ${details_files} ${exceptions_files})
add_subdirectory(Testing)
add_subdirectory(UnitTest)

