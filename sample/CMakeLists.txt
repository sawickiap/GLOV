cmake_minimum_required (VERSION 2.8.11)
project (sample)

SET( MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}" )
foreach(DNAME ${MAIN_FILES})
	file(GLOB FOUND_SOURCES ${DNAME}/*.cpp ${DNAME}/*.c ${DNAME}/*.hpp ${DNAME}/*.h ${DNAME}/*.inl)
	list(APPEND sample_SOURCES ${FOUND_SOURCES})
endforeach()
	SET(TARGET_NAME sample)
	SOURCE_GROUP( sample FILES ${sample_SOURCES} )

add_executable (${PROJECT_NAME} WIN32
${sample_SOURCES} )

include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/Framework)
include_directories(${CMAKE_SOURCE_DIR}/GLOV/include)

link_directories(${CMAKE_SOURCE_DIR}/Framework) 
link_directories(${CMAKE_SOURCE_DIR}/GLOV)

target_link_libraries (${PROJECT_NAME} LINK_PUBLIC GLOV Framework)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} INTERFACE)
