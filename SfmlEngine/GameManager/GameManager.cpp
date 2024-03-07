#include "GameManager.h"
#include <SFML/Graphics.hpp> // Inclure l'en-tête complet pour l'implémentation
#include "Level/Level.h"
#include <cstdlib> // Pour la fonction exit
#include <iostream>

GameManager::GameManager()
{
    // Initialisation supplémentaire si nécessaire
}

void GameManager::Run()
{
    // Vérifier si le level a été instancié
    if (!CurrentLevel)
        return;

    // Instance la fenêtre de jeu
    InitWindow();

    // Vérifier si le fenêtre de jeu a bien été instancié
    if (!Window)
        return;

    // Démarre le level
    CurrentLevel->Start();

    // Instance Clock pour déterminer le Delta Time
    sf::Clock Clock;

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    Window->setView(view);

    // Boucle de jeu principal
    while (Window->isOpen())
    {
        ProcessEvents();

        Update(Clock.restart().asSeconds());

        CurrentLevel->ManageCollision();

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
    // Création de la fenêtre SFML
    Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFML Window");

    // Activer le mode plein écran
    // Window->create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen Windowed", sf::Style::Titlebar | sf::Style::Close);

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
            Window->close();
        else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
            Window->close();
    }

    if (CurrentLevel)
        CurrentLevel->ProcessEvents();
}

void GameManager::Update(const float DeltaTime)
{
    if (!CurrentLevel)
        return;
    CurrentLevel->Update(DeltaTime);
}

void GameManager::Render(sf::RenderWindow &Window)
{
    // Rendu des objets
    if (!CurrentLevel)
        return;
    Window.clear();
    CurrentLevel->Render(Window);
    Window.display();
}
