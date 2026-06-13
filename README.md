# App

### 🚀 Objective
This repository serves as a boilerplate template for developing applications using OpenGL, GLFW, and ImGui.

### ⚙️ Build Instructions
To build the project using CMake/Ninja:

**Dependencies (macOS Example):**
```bash
brew install glfw
# Assuming nlohmann/json and spdlog may also be needed depending on the project stage.
# You may need to adjust these installs based on your project structure:
brew install spdlog
# For Header-Only JSON:
# brew install nlohmann-json
```
1. Create build directory: `mkdir build`
2. Navigate to build: `cd build`
3. Configure CMake: `cmake .. -G Ninja`
4. Build targets: `ninja`

This provides a solid starting point for all visual applications based on this stack.