#include "app.hpp"
#include <iostream>
#include <stdexcept>
#include "spdlog/spdlog.h"

int main() {
    App *app = new App();
    try {
         app->init("Template App", 800, 600);
    }
    catch (const std::runtime_error& e) {
        spdlog::error("Error: {}", e.what());
        return -1;
    }

    app->run();
    app->terminate();

    return 0;
}
