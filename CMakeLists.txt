cmake_minimum_required(VERSION 3.25.1)

project(physics-simulation)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/main.c ${PROJECT_SOURCE_DIR}/glad.c ${PROJECT_SOURCE_DIR}/shader.c)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(vendor/glfw)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw)
