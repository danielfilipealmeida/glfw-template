#include "ApplicationManager.h"
#include <iostream>

using namespace std;

int main() {
    // Define paths for persistence
    const std::string state_filepath = "app_state.json";
    ApplicationManager appManager;

    // --- PHASE 1: Initialization and Load ---
    std::cout << "--- Application Starting ---" << std::endl;
    if (!appManager.initialize(state_filepath)) {
        std::cout << "--- Starting with fresh state. ---" << std::endl;
    } else {
        std::cout << "--- Resuming session from saved state. ---" << std::endl;
    }

    // --- PHASE 2: Main Application Loop ---
    // The application runs here, driven by UI/input events.
    
    // Example: Application loop runs and changes the state
    std::cout << "\n--- Running application logic (e.g., UI thread running) ---" << std::endl;
    
    // Simulate state change
    appManager.updateFloatValue(42.42f);
    appManager.updateStringValue("Hello World!");

    // Read current state representation
    const auto& state = appManager.getCurrentState();
    std::cout << "Current State (in-memory): Float=" << state.floatValue 
              << ", String='" << state.stringValue << "'" << std::endl;


    // --- PHASE 3: Shutdown and Save ---
    std::cout << "\n--- Application Shutting Down ---" << std::endl;
    if (appManager.shutdown(state_filepath)) {
        std::cout << "Shutdown successful. State persisted." << std::endl;
    } else {
        std::cerr << "Shutdown failed. State not persisted." << std::endl;
    }

    return 0;
}