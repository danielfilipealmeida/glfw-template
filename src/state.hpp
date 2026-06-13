#pragma once 

#include <string>
#include <nlohmann/json.hpp>

struct State {
    float floatValue;
    std::string stringValue;

    /**
     * @brief Converts the current state to a JSON object.
     * @return A nlohmann::json object representing the current state.
     */
    nlohmann::json toJson() const;

    /**
     * @brief Loads the state from a JSON object.
     * @param j The nlohmann::json object to load the state from.
     * @throws std::invalid_argument if the JSON object does not contain the required fields.
     */
    void fromJson(const nlohmann::json& j);

    /**
     * @brief Saves the current state to a JSON file.
     * @param filename The name of the file to save the state to.
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Loads the state from a JSON file.
     * @param filename The name of the file to load the state from.
     * @throws std::runtime_error if the file cannot be opened for reading.
     * @throws std::invalid_argument if the JSON object does not contain the required fields.
     */
    void loadFromFile(const std::string& filename);
};