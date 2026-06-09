#pragma once

#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

/**
 * @brief The App struct represents the main application and contains the necessary information and functions to initialize, run, and terminate the application.
 */
struct App {
    std::string appName;
    GLFWwindow* window;
    unsigned int width, height;

    /**
     * @brief Initialize the window with the provided title and dimensions
     * @param _appName the name of the application
     * @param _width the width of the window
     * @param _height the height of the window
     */
    void init(
        std::string _appName,
        unsigned int _width,
        unsigned int _height
    );

    /**
     * @brief Runs the application main loop
     */
    void run();

    /**
     * @brief Cleans up and terminate
     */
    void terminate();
};
