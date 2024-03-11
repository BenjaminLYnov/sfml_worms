#include "GraphData.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "Cell.h"

GraphData::GraphData()
{
}

GraphData::~GraphData()
{
}

void GraphData::SaveGraph()
{
    // Sérialisation des données de jeu en format JSON.
    nlohmann::json JsonData = ToJson();
    std::string SerializedData = JsonData.dump(); // Convertir les données JSON en chaîne de caractères.

    // Cryptage des données sérialisées.
    std::string EncryptedData = XorEncryptDecrypt(SerializedData, SecretKey, 12);

    // Écriture des données cryptées dans un fichier.
    std::ofstream OutFile(Filename, std::ios::binary | std::ios::out); // Ouvrir le fichier en mode binaire avec création.
    OutFile << EncryptedData;                                          // Écrire les données cryptées dans le fichier.
}

void GraphData::LoadGraph()
{
    std::ifstream InFile(Filename, std::ios::binary);                                                      // Ouvrir le fichier en mode binaire pour la lecture.
    std::string EncryptedData((std::istreambuf_iterator<char>(InFile)), std::istreambuf_iterator<char>()); // Lire le contenu crypté du fichier.

    // Décryptage des données lues.
    std::string DecryptedData = XorEncryptDecrypt(EncryptedData, SecretKey, 12);

    try
    {
        // Analyser les données décryptées en tant que JSON.
        nlohmann::json jsonData = nlohmann::json::parse(DecryptedData);

        // Extraction des données spécifiques à partir du JSON.
        CellTypes = jsonData.at("CellTypes").get<std::vector<ECellType>>();
    }
    catch (const nlohmann::json::exception &e)
    {
        // Gestion des erreurs si le JSON est invalide ou corrompu.
        // Certainement modification externe du fichier par une personne makiévélique :D
    }
}

// PRIVATE
nlohmann::json GraphData::ToJson() const
{
    return nlohmann::json{{"CellTypes", CellTypes}};
}

std::string GraphData::XorEncryptDecrypt(const std::string &data, const char *key, size_t keyLength)
{
    std::string output = data; // Copie des données d'entrée pour être transformées.

    for (size_t i = 0; i < data.size(); ++i)
    {                                             // Parcourir chaque caractère des données.
        output[i] = data[i] ^ key[i % keyLength]; // Effectuer une opération XOR entre le caractère des données et le caractère de la clé. Utiliser modulo pour boucler sur la clé.
    }

    return output; // Retourner les données transformées.
}