#include "state.hpp"
#include <fstream>

nlohmann::json State::toJson() const {
    return {
        {"float_value", floatValue},
        {"string_value", stringValue}
    };
}

void State::fromJson(const nlohmann::json& j) {
    floatValue = j.value("float_value", 0.0f);
    stringValue = j.value("string_value", std::string());
}

void State::saveToFile(const std::string& filename) const {
    nlohmann::json j = toJson();
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    file << j.dump(4); // Pretty print with 4 spaces indentation
    file.close();
}

void State::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + filename);   
    }
    nlohmann::json j;
    file >> j;
    fromJson(j);
}