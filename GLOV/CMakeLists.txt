cmake_minimum_required (VERSION 2.8.11)
project (GLOV)

SET( MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/GLOV" )
foreach(DNAME ${MAIN_FILES})
	file(GLOB FOUND_SOURCES ${DNAME}/*.cpp ${DNAME}/*.c ${DNAME}/*.hpp ${DNAME}/*.h ${DNAME}/*.inl)
	list(APPEND GLOV_INCLUDES ${FOUND_SOURCES})
endforeach()
	SET(TARGET_NAME GLOV)
	SOURCE_GROUP( GLOV FILES ${GLOV_INCLUDES} )
SET( MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src" )
foreach(DNAME ${MAIN_FILES})
	file(GLOB FOUND_SOURCES ${DNAME}/*.cpp ${DNAME}/*.c ${DNAME}/*.hpp ${DNAME}/*.h ${DNAME}/*.inl)
	list(APPEND GLOV_SOURCES ${FOUND_SOURCES})
endforeach()
	SET(TARGET_NAME GLOV)
	SOURCE_GROUP( GLOV FILES ${GLOV_SOURCES} )

add_library (GLOV
${GLOV_INCLUDES} 
${GLOV_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${Vulkan_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_link_libraries (${PROJECT_NAME} ${Vulkan_LIBRARIES})

set_target_properties(GLOV PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (GLOV PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} INTERFACE)
