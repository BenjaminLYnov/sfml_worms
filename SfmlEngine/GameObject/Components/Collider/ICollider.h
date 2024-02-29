#pragma once

#include "../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include "memory"
#include "CollisionEvent.h"
#include <functional>
#include <map>
#include "ColliderCallback.h"
#include "Mobility.h"
#include "CollisionResponse.h"

class Transform;
class GameObject;

class ICollider : public IComponent
{
public:
    // Constructeur par défaut
    ICollider();

    virtual ~ICollider(); // Déclaration du destructeur

    // Redéfinition des méthodes virtuelles pures de IComponent.
    virtual void Start() override = 0;
    virtual void Update(const float DeltaTime) override = 0;
    virtual void Render(sf::RenderWindow &Window) override = 0;

    // Méthodes spécifiques à ICollider.
    virtual void OnCollision(std::shared_ptr<ICollider> Other) = 0;
    virtual bool IsOnCollision(std::shared_ptr<ICollider> Other) = 0; // Pour tester une collision

    void SetOffset(const sf::Vector2f &NewOffset);
    // void SetRelativeRotation(float rotation);

    sf::Vector2f GetOffset() const;
    // sf::Vector2f GetRelativeScale() const;
    // float GetRelativeRotation() const;

    void SetWasOnCollision(bool _isOnCollision);

    void SetMobility(const EMobility NewMobility);
    EMobility GetMobility() const;

    void SetCollisionResponse(const ECollisionResponse NewCollisionResponse);
    ECollisionResponse GetCollisionResponse() const;

    template <typename T, typename Method>
    void AddCallback(ECollisionEvent CollisionEvent, T *Obj, Method MethodToBind);

protected:
    sf::Vector2f Offset;

    bool _WasOnCollision = false;

    EMobility Mobility = EMobility::Movable;
    ECollisionResponse CollisionResponse = ECollisionResponse::Block;

    std::map<ECollisionEvent, std::vector<ColliderCallback>> Callbacks;

    void ManageCollisionResponses(GameObject *GameObjectHited, const bool bIsOnCollision);

    bool HasGameObject(GameObject *GameObjectToCheck) const;
    void AddGameObject(GameObject *GameObjectToAdd);
    void RemoveGameObject(GameObject *GameObjectToRemove);

    std::vector<GameObject *> GameObjects;

private:
    virtual void CallCallbacks(ECollisionEvent CollisionEvent, GameObject *GameObjectHited = nullptr);
};

#include "ICollider.tpp" // Inclure les définitions de template
