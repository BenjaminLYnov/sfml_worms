#pragma once

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

// class Level;
#include "Level/Level.h"

class GameManager
{
public:
    GameManager();

    void Run(); // Lance la boucle de jeu principale

    // Ajoute un nouveau niveau au GameManager
    void AddLevel(std::shared_ptr<Level> NewLevel);

    // void SaveGame(const std::string &Filename, const GameData &Data);
    // bool LoadGame(const std::string &Filename, GameData &Data);

private:
    std::shared_ptr<sf::RenderWindow> Window;   // Fenêtre de jeu
    std::vector<std::shared_ptr<Level>> Levels; // Tableau de niveaux

    void InitWindow();                  // Traite les événements de la fenêtre
    void ProcessEvents();               // Traite les événements de la fenêtre
    void Update(const float DeltaTime); // Met à jour la logique du jeu
    void Render(sf::RenderWindow &Window);

    std::shared_ptr<Level> CurrentLevel;
};
