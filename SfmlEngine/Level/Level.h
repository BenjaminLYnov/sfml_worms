#pragma once

#include <vector>
#include "GameObject/GameObject.h"

class Character;
class GameManager;

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

    // Ajoute un GameObject au niveau
    void AddGameObject(std::shared_ptr<GameObject> GameObject);

    std::vector<std::shared_ptr<GameObject>> GetAllGameObjects();

    template <typename T>
    std::vector<std::shared_ptr<T>> GetAllGameObjectByClass();

    template <typename T>
    T *SpawnGameObject(const sf::Vector2f Location = sf::Vector2f(0, 0), const sf::Vector2f Scale = sf::Vector2f(1, 1), const float Rotation = 0.f);

    // Gestionnaires d'événements
    virtual void ProcessEvents();

    // Met à jour tous les GameObjects du niveau
    virtual void Update(const float DeltaTime);

    // Effectue le rendu de tous les GameObjects du niveau
    virtual void Render(sf::RenderWindow &Window) const;

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
    // Character* GetCharacterControlled();

    std::vector<std::shared_ptr<GameObject>> GameObjects;

protected:
    // Character *CharacterControlled;
    std::shared_ptr<Character> CharacterControlled;

    sf::RenderWindow *Window = nullptr;

private:
    float DeltaSecond = 0;
};

#include "Level.tpp"
