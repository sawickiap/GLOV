cmake_minimum_required (VERSION 2.8.11)
project (Framework)

SET( MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}" )
foreach(DNAME ${MAIN_FILES})
	file(GLOB FOUND_SOURCES ${DNAME}/*.cpp ${DNAME}/*.c ${DNAME}/*.hpp ${DNAME}/*.h ${DNAME}/*.inl)
	list(APPEND Framework_SOURCES ${FOUND_SOURCES})
endforeach()
	SET(TARGET_NAME Framework)
	SOURCE_GROUP( Framework FILES ${Framework_SOURCES} )
	
SET( MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Win32" )
foreach(DNAME ${MAIN_FILES})
	file(GLOB FOUND_SOURCES ${DNAME}/*.cpp ${DNAME}/*.c ${DNAME}/*.hpp ${DNAME}/*.h ${DNAME}/*.inl)
	list(APPEND FrameworkWin32_SOURCES ${FOUND_SOURCES})
endforeach()
	SET(TARGET_NAME Framework//Win32)
	SOURCE_GROUP( Framework//Win32 FILES ${FrameworkWin32_SOURCES} )

add_library (Framework
${Framework_SOURCES} 
${FrameworkWin32_SOURCES})
set_target_properties(Framework PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (Framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} INTERFACE)
