#pragma once

#include "../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include "memory"
#include "CollisionEvent.h"
#include <functional>
#include <map>

class Transform;
class GameObject;

enum Layers
{
    ALL = 1,
    STATIC = (1 << 1),
    ENNEMY = (1 << 2),
};

class ICollider : public IComponent
{
public:
    // Constructeur par défaut
    ICollider();

    virtual ~ICollider(); // Déclaration du destructeur

    using Callback = std::function<void()>;

    // Redéfinition des méthodes virtuelles pures de IComponent.
    virtual void Start() override = 0;
    virtual void Update(const float DeltaTime) override = 0;
    virtual void Render(sf::RenderWindow &Window) override = 0;

    // Méthodes spécifiques à ICollider.
    virtual void OnCollision(std::shared_ptr<ICollider> Other);    // Appelé lors d'un test de collision
    virtual bool IsOnCollision(std::shared_ptr<ICollider> Other) = 0; // Pour tester une collision

    void SetOffset(const sf::Vector2f &NewOffset);
    // void SetRelativeRotation(float rotation);

    sf::Vector2f GetOffset() const;
    // sf::Vector2f GetRelativeScale() const;
    // float GetRelativeRotation() const;

    void SetWasOnCollision(bool _isOnCollision);
    void SetLayer(Layers NewLayers);
    void AddLayer(Layers LayersToAdd);
    void RemoveLayer(Layers LayerSToRemove);

    bool HasLayer(Layers LayersToCheck);

    char GetMask() const;

    template <typename T, typename Method, typename... Args>
    void AddCallback(ECollisionEvent CollisionEvent, T *Obj, Method MethodToBind, Args... args);

    virtual void CallCallbacks(ECollisionEvent CollisionEvent);

protected:
    sf::Vector2f Offset;

    bool _WasOnCollision = false;

    unsigned char Mask = Layers::ALL; 

    std::map<ECollisionEvent, std::vector<Callback>> Callbacks;

    bool HasGameObject(GameObject* GameObjectToCheck) const;
    void AddGameObject(GameObject* GameObjectToAdd);
    void RemoveGameObject(GameObject* GameObjectToRemove);

    // GameObject *GameObjects;
    std::vector<GameObject*> GameObjects;
};

#include "ICollider.tpp" // Inclure les définitions de template
