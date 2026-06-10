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

#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100 (WebGL 1.0)
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(IMGUI_IMPL_OPENGL_ES3)
        // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
        const char* glsl_version = "#version 300 es";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    // Get the content scale for the primary monitor to adjust the UI scaling accordingly
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width * main_scale, height * main_scale, appName.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    ui.init(window, main_scale, glsl_version);
}


void App::run() {
    while (!glfwWindowShouldClose(window)) {
        // Check for key presses
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            spdlog::info("Q pressed. Exiting...");
            glfwSetWindowShouldClose(window, true);
        }

        glfwMakeContextCurrent(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ui.render();
        ui.draw();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::terminate() {
     glfwTerminate();
}
