cmake_minimum_required(VERSION 3.15)
project(openglworkshop1 VERSION 1.0.0 LANGUAGES CXX)

# c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# GLFW (we don't need docs, tests or examples)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

# GLEW (static only, no shared/dynamic libs)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG glew-cmake-2.2.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw glew)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/shader.cpp
    vendor/stb_image/stb_image.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include SYSTEM PRIVATE vendor)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw libglew_static OpenGL::GL)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
