#include "ui.hpp"


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

void UI::render() {
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    
    ImGui::Begin("ROOT", nullptr);                   
    ImGui::Text("This is some useful text.");
    ImGui::Button("Save");
    ImGui::End();

    ImGui::EndFrame();

    ImGui::Render();
}

void UI::draw() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}