#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include "CellType.h"

class GraphData
{
public:
    GraphData();
    ~GraphData();

    int score;
    int level;

    void SaveGraph();
    void LoadGraph();

    std::vector<ECellType> CellTypes;

private:
    const std::string Filename = "data.sav";
    const char *SecretKey = "Tu es deja mort.";

    // Fonction pour convertir GameData en JSON
    nlohmann::json ToJson() const;

    std::string XorEncryptDecrypt(const std::string &data, const char *key, size_t keyLength);
};

#endif