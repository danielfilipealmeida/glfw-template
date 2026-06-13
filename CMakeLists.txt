# setting variables
set(PROJECT_NAME "App")
set(LIB_PATH "../../../libs/")
set(IMGUI_PATH "${LIB_PATH}/imgui/")
set(STATIC_DIR ${CMAKE_SOURCE_DIR}/static)
set(DEST_STATIC_DIR ${CMAKE_CURRENT_BINARY_DIR}/static)

cmake_minimum_required(VERSION 3.18) # Bump minimum version for modern commands
project(${PROJECT_NAME})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ImGui library
add_library(imgui
  ${IMGUI_PATH}/imgui.cpp
  ${IMGUI_PATH}/imgui_draw.cpp
  ${IMGUI_PATH}/imgui_tables.cpp
  ${IMGUI_PATH}/imgui_widgets.cpp
  ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
  ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
  ${IMGUI_PATH}/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imgui PUBLIC
  ${IMGUI_PATH}
  ${IMGUI_PATH}/backends
  ${IMGUI_PATH}/misc/cpp
)
target_link_libraries(imgui PRIVATE glfw)


include_directories(${IMGUI_PATH})

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp
    src/ui/ui.cpp
    src/state.cpp
    )

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL 
    glfw 
    nlohmann_json::nlohmann_json
    spdlog::spdlog 
    imgui
)

# Enable OpenGL support
target_compile_definitions(
  ${PROJECT_NAME} 
  PRIVATE FORCE_OPENGL
  GL_SILENCE_DEPRECATION
)

# Copy static files after build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${STATIC_DIR} ${DEST_STATIC_DIR}
)