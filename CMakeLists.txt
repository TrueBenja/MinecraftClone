cmake_minimum_required(VERSION 3.24)
project(MinecraftClone LANGUAGES C CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(thirdparty/glfw)

add_subdirectory(src)

target_include_directories(MinecraftClone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(MinecraftClone PRIVATE glfw)
