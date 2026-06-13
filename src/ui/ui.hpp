#pragma once

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../state.hpp"

struct UI {

    float mainScale = 1.0f;
        
    /**
     * Initializes the UI system with the given GLFW window and GLSL version.
     * @param window The GLFW window to which the UI will be attached.
     * @param main_scale The scaling factor for the UI elements, allowing for adjustments in size based on user preferences or display settings.
     * @param glsl_version The GLSL version to be used for rendering the UI.
     */
    void init(GLFWwindow* window, float main_scale, const char* glsl_version);

    /**
     * Loads the font for the UI. This function should be called to set up the font used in the UI elements.
     * @param io The ImGuiIO structure that contains the font configuration and settings.
     */
    void loadFont(ImGuiIO& io);

    /**
     * Renders the UI elements. This function should be called every frame to update and display the UI.
     * It handles the rendering of all UI components and ensures that they are displayed correctly on the screen.
     */
    void render(State& state);

    /**
     * Draws the UI elements. This function is responsible for the actual drawing of the UI components on the screen.
     */
    void draw();

    /**
     * Displays a popup message with the given title and message content.
     * @param title The title of the popup window.
     * @param message The message content to be displayed in the popup.
     */
    void showPopup(const char* title, const char* message);
};