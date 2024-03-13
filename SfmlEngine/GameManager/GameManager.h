#pragma once

#include <string>
#include <memory>
#include <map>

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class Level;

class GameManager
{
public:
    GameManager();

    void Run(); // Lance la boucle de jeu principale

    // Ajoute un nouveau niveau au GameManager
    void AddLevel(const std::string LevelName, std::shared_ptr<Level> NewLevel);
    void LoadLevel(const std::string LevelName);
    void SetStartLevel(const std::string LevelName);

private:
    std::shared_ptr<sf::RenderWindow> Window;   // Fenêtre de jeu
    // std::vector<std::shared_ptr<Level>> Levels; // Tableau de niveaux
    std::map<std::string, std::shared_ptr<Level>> Levels; // Tableau de niveaux

    void InitWindow();                  // Traite les événements de la fenêtre
    void ProcessEvents();               // Traite les événements de la fenêtre
    void Update(const float DeltaTime); // Met à jour la logique du jeu
    void Render(sf::RenderWindow &Window) const;
    void RenderUI(sf::RenderWindow &Window) const;

    bool HasLevel(const std::string LevelName) const;
    std::shared_ptr<Level> CurrentLevel;
};
