#include "GameManager.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level/Level.h"
#include <cstdlib> // Pour la fonction exit
#include <iostream>

GameManager::GameManager()
{
    // Initialisation supplémentaire si nécessaire
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
    if (!CurrentLevel)
    {
        std::cout << "No Level";
        return;
    }

    InitWindow();

    if (!Window)
    {
        std::cout << "No Window";
        return;
    }

    CurrentLevel->Start();

    sf::Clock Clock;
    while (Window->isOpen())
    {
        ProcessEvents();
        Update(Clock.restart().asSeconds());
        Render(*Window);
    }
}

void GameManager::AddLevel(std::shared_ptr<Level> NewLevel)
{
    if (!NewLevel)
        return;

    if (!CurrentLevel)
        CurrentLevel = NewLevel;

    Levels.push_back(NewLevel);
}

// void GameManager::SaveGame(const std::string& filename, const GameData& data) {
//     std::ofstream outFile(filename);
//     if (!outFile) {
//         std::cerr << "Impossible d'ouvrir le fichier pour la sauvegarde." << std::endl;
//         return;
//     }

//     outFile << data.ToJson().dump(4);
// }

// bool GameManager::LoadGame(const std::string& filename, GameData& data) {
//     std::ifstream inFile(filename);
//     if (!inFile) {
//         std::cerr << "Impossible d'ouvrir le fichier pour charger les données." << std::endl;
//         return false;
//     }

//     nlohmann::json jsonData;
//     inFile >> jsonData;
//     data = GameData::FromJson(jsonData);

//     return true;
// }

// PRIVATE

void GameManager::InitWindow()
{
    Window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Window");
    // Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML Window");

    // Limite les FPS à 60
    Window->setFramerateLimit(60);
    // Window->setVerticalSyncEnabled(true);
}

void GameManager::ProcessEvents()
{
    sf::Event Event;
    while (Window->pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
        {
            Window->close();
        }
        // Autres gestionnaires d'événements ici
    }
}

void GameManager::Update(const float DeltaTime)
{
    if (CurrentLevel)
        CurrentLevel->Update(DeltaTime);
}

void GameManager::Render(sf::RenderWindow &Window)
{
    Window.clear();

    // Rendu des objets
    if (CurrentLevel)
        CurrentLevel->Render(Window);

    Window.display();
}
