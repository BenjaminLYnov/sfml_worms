#pragma once

#include <vector>
#include "GameObject/GameObject.h"

class Canvas;
class Character;
class GameManager;
class SquareCollider;

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class Level
{
public:
    virtual ~Level() = default;
    Level();

    virtual void Start();

    // Met à jour tous les GameObjects du niveau
    virtual void Update(const float DeltaTime);

    // Effectue le rendu de tous les GameObjects du niveau
    virtual void Render(sf::RenderWindow &Window) const;

    // Ajoute un GameObject au niveau
    void AddGameObject(std::shared_ptr<GameObject> GameObject);

    void AddCanvas(std::shared_ptr<Canvas> Canvas);

    std::vector<std::shared_ptr<GameObject>> GetAllGameObjects();

    template <typename T>
    std::vector<std::shared_ptr<T>> GetAllGameObjectByClass();

    template <typename T>
    std::shared_ptr<T> SpawnGameObject(const sf::Vector2f Location = sf::Vector2f(0, 0), const sf::Vector2f Scale = sf::Vector2f(1, 1), const float Rotation = 0.f);

    // Gestionnaires d'événements
    virtual void ProcessEvents();

    void SetWindow(sf::RenderWindow *_Window);

    sf::RenderWindow *GetWindow();

    // Assigne le Character que le joueur contrôle dans le level
    // void SetCharacterControlled(Character* NewCharacterControlled);
    void SetCharacterControlled(std::shared_ptr<Character> NewCharacterControlled = std::shared_ptr<Character>());

    void ManageCollision();

    void RemoveGameObject(GameObject *GameObjectToRemove);

    float GetWorldDeltaSecond() const;

    GameManager *GM = nullptr;

    std::shared_ptr<Character> GetCharacterControlled();

    std::vector<std::shared_ptr<GameObject>> GameObjects;
    std::vector<std::shared_ptr<Canvas>> CanvasList;

protected:
    std::shared_ptr<Character> CharacterControlled;

    sf::RenderWindow *Window = nullptr;

    void ManageCollisionByGameObjects(std::vector<std::shared_ptr<GameObject>> GameObjectsToManage);
    void InitZone();

protected:
    float DeltaSecond = 0;

    // ZONES (To optimize collisions)
    std::vector<std::shared_ptr<SquareCollider>> Zones;
    const int Lines = 5;
    const int Cols = 20;
    const sf::Vector2f ZoneSize = sf::Vector2f(100, 100);

    std::vector<std::shared_ptr<GameObject>> GetGameObjectsByZone(std::shared_ptr<SquareCollider> &ZoneToGetGameObjects);
};

#include "Level.tpp"
