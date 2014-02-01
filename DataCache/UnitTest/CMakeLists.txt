file(GLOB interface_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp)
file(GLOB implementation_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp)

source_group("Source" FILES ${implementation_files} ${interface_files})

if(WIN32)

else()
	include_directories("/Volumes/proj/unittest++/")
	set(UNITTEST++_LIBRARIES "/Volumes/proj/unittest++/libUnitTest++.a")
endif()

add_executable(DataCache-UT ${implementation_files} ${interface_files})
target_link_libraries(DataCache-UT DataCache DataCacheTesting ${UNITTEST++_LIBRARIES})

add_custom_command(TARGET DataCache-UT POST_BUILD COMMAND @echo off)
add_custom_command(TARGET DataCache-UT POST_BUILD COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/DataCache-UT)


