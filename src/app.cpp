#include "app.hpp"
#include <stdexcept>
#include "spdlog/spdlog.h"

// move to use spdlogs
void glfwErrorCallback(int error, const char* description) {
    spdlog::error("GLFW Error {}: {}", error, description);
}

void App::init(
    std::string _appName,
    unsigned int _width,
    unsigned int _height
) {
    appName = _appName;
    width = _width;
    height = _height;

    // set the callback error
    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Set OpenGL version (4.6 in this case)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, appName.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
}


void App::run() {
    while (!glfwWindowShouldClose(window)) {
        // Check for key presses
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            spdlog::info("Q pressed. Exiting...");
            glfwSetWindowShouldClose(window, true);
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::terminate() {
     glfwTerminate();
}
