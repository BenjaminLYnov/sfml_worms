#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct GameData {
    int Score;
    int Level;
    // Ajoutez d'autres membres au besoin.

    nlohmann::json ToJson() const {
        return nlohmann::json{{"Score", Score}, {"Level", Level}};
    }

    static GameData FromJson(const nlohmann::json& j) {
        return GameData{
            j.at("Score").get<int>(),
            j.at("Level").get<int>()
        };
    }
};
