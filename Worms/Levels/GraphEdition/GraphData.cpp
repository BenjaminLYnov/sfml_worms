#include "GraphData.h"
#include <fstream>

GraphData::GraphData()
{
}

GraphData::~GraphData()
{
}

nlohmann::json GraphData::toJson() const
{
    return nlohmann::json{{"score", score}, {"level", level}};
}

void GraphData::saveGame()
{
    // Sérialisation des données de jeu en format JSON.
    nlohmann::json jsonData = toJson();
    std::string serializedData = jsonData.dump(); // Convertir les données JSON en chaîne de caractères.

    // Cryptage des données sérialisées.
    std::string encryptedData = xorEncryptDecrypt(serializedData, "Tu es deja mort.", 12);

    const std::string filename = "data.sav";

    // Écriture des données cryptées dans un fichier.
    std::ofstream outFile(filename, std::ios::binary | std::ios::out); // Ouvrir le fichier en mode binaire avec création.
    outFile << encryptedData;                                          // Écrire les données cryptées dans le fichier.
}

// PRIVATE
std::string GraphData::xorEncryptDecrypt(const std::string &data, const char *key, size_t keyLength)
{
    std::string output = data; // Copie des données d'entrée pour être transformées.

    for (size_t i = 0; i < data.size(); ++i)
    {                                             // Parcourir chaque caractère des données.
        output[i] = data[i] ^ key[i % keyLength]; // Effectuer une opération XOR entre le caractère des données et le caractère de la clé. Utiliser modulo pour boucler sur la clé.
    }

    return output; // Retourner les données transformées.
}