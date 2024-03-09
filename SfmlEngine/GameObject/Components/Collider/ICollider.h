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
#include <memory>
#include "HitResult.h"

class Transform;
class GameObject;
class SquareCollider;
class CircleCollider;
class TriangleCollider;
class Rigidbody;

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
    virtual void CancelCollision(ICollider *Other) = 0;

    // Méthodes spécifiques à ICollider.
    void ManageCollision(ICollider *Other);
    HitResult TestCollision(const ICollider *Other, const bool bCheckMirror = true) const;

    void SetOffset(const sf::Vector2f &NewOffset);
    // void SetRelativeRotation(float rotation);

    sf::Vector2f GetOffset() const;
    // sf::Vector2f GetRelativeScale() const;
    // float GetRelativeRotation() const;

    void SetMobility(const EMobility NewMobility);
    EMobility GetMobility() const;

    void SetCollisionResponse(const ECollisionResponse NewCollisionResponse);
    ECollisionResponse GetCollisionResponse() const;

    template <typename T, typename Method>
    void AddCallback(ECollisionEvent CollisionEvent, T *Obj, Method MethodToBind);

    void InitCollider();

    SquareCollider* Square;
    CircleCollider* Circle;
    TriangleCollider* Triangle;

    bool bEnableCollision = false;

protected:
    sf::Vector2f Offset;

    bool _WasOnCollision = false;

    EMobility Mobility = EMobility::Movable;
    ECollisionResponse CollisionResponse = ECollisionResponse::Block;

    std::map<ECollisionEvent, std::vector<ColliderCallback>> Callbacks;

    void ManageCollisionCallbacks(GameObject *GameObjectHited, const bool bIsOnCollision);

    bool HasGameObject(GameObject *GameObjectToCheck) const;
    void AddGameObject(GameObject *GameObjectToAdd);
    void RemoveGameObject(GameObject *GameObjectToRemove);

    std::vector<GameObject *> GameObjects;

    void Overlap(ICollider *Other);
    void Block(ICollider *Other);

    void Static(ICollider *Other);
    void Movable(ICollider *Other);

    void MoveByRigidbody(const HitResult Hit);
    void RestrictRigidbody(const sf::Vector2f Normal);

    
private:
    virtual void CallCallbacks(ECollisionEvent CollisionEvent, GameObject *GameObjectHited = nullptr);
};

#include "ICollider.tpp" // Inclure les définitions de template
