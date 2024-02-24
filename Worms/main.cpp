#include <iostream>
#include "Levels/MainMenu/MainMenu.h"
#include "GameManager/GameManager.h"

// Inclusion l'entête Resources necéssaire pour instancier les sprites
#include "Levels/MainMenu/LevelRules.h"
#include "Resources/Resources.h"

// #include <fstream>
// #include <string>
// #include <lib/nlohmann/json.hpp>
// #include <algorithm>

// struct GameData
// {
//     int score;
//     int level;
//     std::vector<int> enemyPositions;
//     // ... autres données de jeu ...

//     // Fonction pour convertir GameData en JSON
//     nlohmann::json toJson() const
//     {
//         return nlohmann::json{{"score", score}, {"level", level}};
//     }
// };

// std::string xorEncryptDecrypt(const std::string &data, const char *key, size_t keyLength) {
//     std::string output = data; // Copie des données d'entrée pour être transformées.

//     for (size_t i = 0; i < data.size(); ++i) { // Parcourir chaque caractère des données.
//         output[i] = data[i] ^ key[i % keyLength]; // Effectuer une opération XOR entre le caractère des données et le caractère de la clé. Utiliser modulo pour boucler sur la clé.
//     }

//     return output; // Retourner les données transformées.
// }


// void saveGame(const std::string &filename, const GameData &data) {
//     // Sérialisation des données de jeu en format JSON.
//     nlohmann::json jsonData = data.toJson();
//     std::string serializedData = jsonData.dump(); // Convertir les données JSON en chaîne de caractères.

//     // Cryptage des données sérialisées.
//     std::string encryptedData = xorEncryptDecrypt(serializedData, "YourSecretKey", 12);

//     // Écriture des données cryptées dans un fichier.
//     std::ofstream outFile(filename, std::ios::binary); // Ouvrir le fichier en mode binaire.
//     outFile << encryptedData; // Écrire les données cryptées dans le fichier.
// }


// bool loadGame(const std::string& filename, GameData& data) {
//     std::ifstream inFile(filename, std::ios::binary); // Ouvrir le fichier en mode binaire pour la lecture.
//     std::string encryptedData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>()); // Lire le contenu crypté du fichier.

//     // Décryptage des données lues.
//     std::string decryptedData = xorEncryptDecrypt(encryptedData, "YourSecretKey", 12);

//     try {
//         // Analyser les données décryptées en tant que JSON.
//         nlohmann::json jsonData = nlohmann::json::parse(decryptedData);

//         // Extraction des données spécifiques à partir du JSON.
//         data.score = jsonData.at("score").get<int>(); // Extraire le score.
//         data.level = jsonData.at("level").get<int>(); // Extraire le niveau.
//         // Charger d'autres membres si nécessaire...
//     } catch (const nlohmann::json::exception& e) {
//         // Gestion des erreurs si le JSON est invalide ou corrompu.
//         std::cerr << "Erreur lors du chargement des données de jeu : " << e.what() << std::endl;
//         return false; // Retourner false en cas d'échec du chargement.
//     }

//     return true; // Retourner true si le chargement a réussi.
// }


int main()
{
    // GameData myGameData{100, 2};

    // // Sauvegarde des données
    // saveGame("game_data.sav", myGameData);

    // // Essayer de charger les données corrompues
    // GameData loadedGameData;
    // bool success = loadGame("game_data.sav", loadedGameData);
    // if (success) {
    //     std::cout << "Données chargées avec succès." << std::endl;
    // } else {
    //     std::cout << "Échec du chargement des données." << std::endl;
    // }

    // std::cout << loadedGameData.level << "\n";
    // std::cout << loadedGameData.score << "\n";

    // Instance Game Manager
    std::unique_ptr<GameManager> SGameManager = std::make_unique<GameManager>();

    // Add Level
    //SGameManager->AddLevel(std::make_shared<MainMenu>());
    SGameManager->AddLevel(std::make_shared<LevelRules>());

    // Run Game Loop
    SGameManager->Run();

    return 0;
}
