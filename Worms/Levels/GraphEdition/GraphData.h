#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#pragma once
#include <nlohmann/json.hpp>
#include <string>

class GraphData
{
public:
    GraphData();
    ~GraphData();

    int score;
    int level;

    // Fonction pour convertir GameData en JSON
    nlohmann::json toJson() const;

    void saveGame();

private:    
    std::string xorEncryptDecrypt(const std::string &data, const char *key, size_t keyLength);
};

#endif