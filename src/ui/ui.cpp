#include "ui.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "spdlog/spdlog.h"

void UI::init(GLFWwindow* window,  float main_scale, const char* glsl_version) {
    this->mainScale = main_scale;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    #ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
    #endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    loadFont(io);
}

void UI::loadFont(ImGuiIO& io) {
    ImFont* font = io.Fonts->AddFontFromFileTTF("static/fonts/HackNerdFont-Regular.ttf", 14.0f * mainScale);
    io.FontDefault = font;
}

void UI::render(State& state) {
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    
    ImGui::Begin("Window", nullptr);          

   ImGui::TextWrapped(
        "This is a template for a GLFW application with ImGui integration." 
        "You can modify the definition of the State struct in src/state.hpp to add more fields as needed." 
        "Update your ui controls here in src/ui/ui.cpp to reflect the changes in the State struct." 
        "If the ui is complex, split it into multiple files in the src/ui directory and include them here." 
   );
   ImGui::TextWrapped(
        "The template already has state load and save functionality implemented in src/state.cpp and src/state.hpp." 
        "The state is automatically loaded from state.json on startup and saved to state.json when the Save button is pressed." 
        "If the state.json file does not exist or is invalid, the application will use default values for the state fields." 
        "You can customize the default values in the App::App() constructor in src/app.cpp." 
        "The state is passed to the UI::render() function, where you can create ImGui controls to modify the state fields."
    );

    ImGui::Separator();

    ImGui::SliderFloat("Float Value", &state.floatValue, 0.0f, 1.0f);
    ImGui::InputText("String Value", &state.stringValue);
    
    
    if (ImGui::Button("Save")) {
        try {
            state.saveToFile("state.json");
            spdlog::info("State saved to state.json");
        } catch (const std::exception& e) {
            spdlog::error("Failed to save state: {}", e.what());
            showPopup("Error", e.what());
        }
    }
    ImGui::End();

    ImGui::EndFrame();

    ImGui::Render();
}

void UI::draw() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::showPopup(const char* title, const char* message) {
        ImGui::OpenPopup(title);
        if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("%s", message);
            if (ImGui::Button("OK")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }