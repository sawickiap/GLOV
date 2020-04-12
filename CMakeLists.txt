cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project( GLOV_Lib )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}" )
SET( CMAKE_EXTERNAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external" )

find_package(Vulkan REQUIRED FATAL_ERROR) # error

IF( MSVC )
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
	SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:library" )
	ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
	ADD_DEFINITIONS( -D_CRT_SECURE_NO_DEPRECATE )
ELSE()
	ADD_DEFINITIONS( -std=c++17 )
ENDIF( MSVC )

#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )
#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/Tests )

#INCLUDE_DIRECTORIES( Math )
#INCLUDE_DIRECTORIES(Vulkan::Vulkan)

#target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
#target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

#include_directories(${CMAKE_SOURCE_DIR}/external/stb)
#link_directories(${CMAKE_SOURCE_DIR}/external/stb) 

#add_subdirectory(${CMAKE_EXTERNAL_PATH}/imgui)
#add_subdirectory(${CMAKE_EXTERNAL_PATH}/fmt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Framework)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GLOV)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sample)

#target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Vulkan::Vulkan)

#INSTALL ( TARGETS ${PROJECT_NAME}
#                  RUNTIME DESTINATION bin
#                  LIBRARY DESTINATION lib
#                  ARCHIVE DESTINATION lib/static )
