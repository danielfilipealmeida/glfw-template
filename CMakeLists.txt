# setting variables
set(PROJECT_NAME "App")
set(LIB_PATH "../../../libs/")
set(IMGUI_PATH "${LIB_PATH}/imgui/")

cmake_minimum_required(VERSION 3.18) # Bump minimum version for modern commands
project(${PROJECT_NAME})

# Fetch spdlog dependency
include(FetchContent)
FetchContent_Declare(
    spdlog_dependency
    GIT_REPOSITORY "https://github.com/gabime/spdlog" # Placeholder URL
    GIT_TAG "v1.17.0" # Specific tag/version
    SOURCE_DIR ${CMAKE_BINARY_DIR}/spdlog
)
FetchContent_MakeAvailable(spdlog_dependency)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")



include_directories(${IMGUI_PATH})

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
    )

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw spdlog::spdlog)

# Enable OpenGL support
target_compile_definitions(${PROJECT_NAME} PRIVATE FORCE_OPENGL)
