cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(OGL VERSION 1.0)

file(GLOB_RECURSE SOURCE_FILES
		 ${CMAKE_SOURCE_DIR}/src/*.c)

file(GLOB_RECURSE HEADER_FILES
		 ${CMAKE_SOURCE_DIR}/src/*.h)


add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
#find_package(OpenGL REQUIRED)

find_package(glfw3 REQUIRED)
#message(STATUS "FOUND GLFW3 in ${GLFW3_INCLUDE_DIR}")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(${PROJECT_NAME} glfw)

add_library(GLAD "vendor/glad.c")

set(LIBS glfw3 GLAD)

include_directories(
					"${CMAKE_SOURCE_DIR}/src"
					"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} ${LIBS})
