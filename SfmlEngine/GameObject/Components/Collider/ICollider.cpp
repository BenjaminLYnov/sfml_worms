#include "ICollider.h"
#include "GameObject/GameObject.h"
#include <iostream>
#include "ColliderChecker.h"
#include "SquareCollider.h"
#include "CircleCollider.h"
#include "TriangleCollider.h"
#include "GameObject/Character/Character.h"
#include <typeinfo>
#include "HitResult.h"
#include "../Rigidbody/Rigidbody.h"
#include "Math/Vector/Vector.h"

ICollider::ICollider()
{
}

ICollider::~ICollider()
{
}

void ICollider::InitCollider()
{
    Square = dynamic_cast<SquareCollider *>(this);
    Circle = dynamic_cast<CircleCollider *>(this);
    Triangle = dynamic_cast<TriangleCollider *>(this);
}

void ICollider::ManageCollision(ICollider *Other)
{
    switch (GetCollisionResponse())
    {
    case ECollisionResponse::Ignore:
        return;
        break;
    case ECollisionResponse::Overlap:
        Overlap(Other);
        break;
    case ECollisionResponse::Block:
        Block(Other);
        break;
    default:
        break;
    }
}

HitResult ICollider::TestCollision(const ICollider *Other, const bool bCheckMirror) const
{
    if (Circle && Other->Circle)
    {
        return ColliderChecker::TestCollision(*Circle, *Other->Circle);
    }
    else if (Square && Other->Square)
    {
        return ColliderChecker::TestCollision(*Square, *Other->Square);
    }
    // else if (Triangle && Other->Triangle)
    // {
    //     return ColliderChecker::TestCollision(*Triangle, *Other->Triangle);
    // }
    else if (Square && Other->Circle)
    {
        return ColliderChecker::TestCollision(*Square, *Other->Circle);
    }
    else if (Square && Other->Triangle)
    {
        return ColliderChecker::TestCollision(*Square, *Other->Triangle);
    }
    else if (Circle && Other->Triangle)
    {
        return ColliderChecker::TestCollision(*Circle, *Other->Triangle);
    }

    if (bCheckMirror)
        return Other->TestCollision(this, false);

    return HitResult();
}

void ICollider::SetOffset(const sf::Vector2f &NewOffset)
{
    Offset = NewOffset;
}

sf::Vector2f ICollider::GetOffset() const
{
    return Offset;
}

EMobility ICollider::GetMobility() const
{
    return Mobility;
}

void ICollider::SetMobility(EMobility NewMobility)
{
    Mobility = NewMobility;
}

ECollisionResponse ICollider::GetCollisionResponse() const
{
    return CollisionResponse;
}

void ICollider::SetCollisionResponse(ECollisionResponse NewCollisionResponse)
{
    CollisionResponse = NewCollisionResponse;
}
//////////////////////////////////////////////////////
// PROTECTED

bool ICollider::HasGameObject(GameObject *GameObjectToCheck) const
{
    return std::find(GameObjects.begin(), GameObjects.end(), GameObjectToCheck) != GameObjects.end();
}

void ICollider::AddGameObject(GameObject *GameObjectToAdd)
{
    if (HasGameObject(GameObjectToAdd))
        return;
    GameObjects.push_back(GameObjectToAdd);
}

void ICollider::RemoveGameObject(GameObject *GameObjectToRemove)
{
    if (!HasGameObject(GameObjectToRemove))
        return;

    auto it = std::find(GameObjects.begin(), GameObjects.end(), GameObjectToRemove);
    if (it != GameObjects.end())
    {
        GameObjects.erase(it);
    }
}

void ICollider::ManageCollisionCallbacks(GameObject *GameObjectHited, bool bIsOnCollision)
{
    if (!GameObjectHited)
        return;

    // S'il n'y pas collision
    if (!bIsOnCollision)
    {
        // S'il l'autre game object est déjà dans le tableau GameObjects, alors il vient de sortir de la collision
        if (HasGameObject(GameObjectHited))
        {
            // Enlève l'autre du tableau GameObjects
            RemoveGameObject(GameObjectHited);

            // Appel des callbacks lors de l'exit
            CallCallbacks(ECollisionEvent::Exit, GameObjectHited);
        }
        return;
    }

    // Il y a collision

    // S'il l'autre game object n'est déjà dans le tableau GameObjects, alors il vient de rentrer en collision
    if (!HasGameObject(GameObjectHited))
    {
        // Ajoute l'autre au tableau GameObjects
        AddGameObject(GameObjectHited);

        // Appel des callbacks lors de la collision entrant
        CallCallbacks(ECollisionEvent::Enter, GameObjectHited);
    }

    // Appel des callbacks de tant qu'il y a collision
    CallCallbacks(ECollisionEvent::Stay, GameObjectHited);
}

void ICollider::Overlap(ICollider *Other)
{
    if (!Other)
        return;
    if (Other->GetCollisionResponse() == ECollisionResponse::Ignore)
        return;
    const HitResult Hit = TestCollision(Other);
    Other->ManageCollisionCallbacks(GetOwner(), Hit.bIsOnCollision);
    ManageCollisionCallbacks(Other->GetOwner(), Hit.bIsOnCollision);
}

void ICollider::Block(ICollider *Other)
{
    if (!Other)
        return;

    switch (Other->GetCollisionResponse())
    {
    case ECollisionResponse::Ignore:
        return;
        break;
    case ECollisionResponse::Overlap:
        Overlap(Other);
        return;
        break;
    default:
        break;
    }

    // Other->GetCollisionResponse() is BLOCK

    switch (GetMobility())
    {
    case EMobility::Static:
        if (Other->GetMobility() == EMobility::Static)
            return;
        Static(Other);
        break;
    case EMobility::Movable:
        Movable(Other);
        break;
    default:
        break;
    }
}

void ICollider::Static(ICollider *Other)
{
    const HitResult Hit = TestCollision(Other);

    // Dégage l'autre s'il y a collision
    if (Hit.bIsOnCollision)
    {
        Rigidbody *Rb = Other->GetOwner()->GetComponent<Rigidbody>();

        // Annuler la collision
        if (!Rb)
        {
            Other->GetOwner()->AddWorldPosition(Hit.Normal * Hit.CancelDistance);
            if (Hit.Normal.y < 0)
            {
                Other->GetOwner()->AddWorldPosition(sf::Vector2f(0, -1) * Hit.CancelDistance);
            }
            else
            {
                Other->GetOwner()->AddWorldPosition(Hit.Normal * Hit.CancelDistance);
            }
        }

        Other->MoveByRigidbody(Hit);
    }

    Other->ManageCollisionCallbacks(GetOwner(), Hit.bIsOnCollision);
    ManageCollisionCallbacks(Other->GetOwner(), Hit.bIsOnCollision);
}

void ICollider::Movable(ICollider *Other)
{
    switch (Other->GetMobility())
    {
    case EMobility::Static:
        Other->Static(this);
        return;
        break;
    default:
        break;
    }

    // Other->GetMobility() is Movable

    const HitResult Hit = TestCollision(Other);

    ManageCollisionCallbacks(Other->GetOwner(), Hit.bIsOnCollision);
    Other->ManageCollisionCallbacks(GetOwner(), Hit.bIsOnCollision);
}

void ICollider::RestrictRigidbody(const sf::Vector2f Normal)
{
    Rigidbody *Rb = GetOwner()->GetComponent<Rigidbody>();
    if (!Rb)
        return;
    if (Normal.x)
        Rb->SetVelocity(sf::Vector2f(0, Rb->GetVelocity().y));
    if (Normal.y)
        Rb->SetVelocity(sf::Vector2f(Rb->GetVelocity().x, 0));
}

void ICollider::MoveByRigidbody(const HitResult Hit)
{
    Rigidbody *Rb = GetOwner()->GetComponent<Rigidbody>();

    if (!Rb)
        return;

    // Vérifier l'angle entre l'objet et la normal
    float ObjectToPenteAngle;
    float PenteAngle;
    sf::Vector2f Move = sf::Vector2f(0, 0);

    if (Hit.Normal == sf::Vector2f(0, 0))
        return;

    PenteAngle = Vector::DotProduct(sf::Vector2f(0, -1), Hit.Normal);

    if (PenteAngle == 0)
    {
        GetOwner()->AddWorldPosition(Hit.Normal * Hit.CancelDistance);
        RestrictRigidbody(sf::Vector2f(0, 1));
        return;
    }

    Move.x = Rb->GetVelocity().x;

    if (Rb->GetVelocity().x > 0)
    {
        ObjectToPenteAngle = Vector::DotProduct(sf::Vector2f(1, 0), Hit.Normal);
    }
    else
    {
        ObjectToPenteAngle = Vector::DotProduct(sf::Vector2f(-1, 0), Hit.Normal);
    }

    if (PenteAngle <= Rb->MaxAnglePente)
        RestrictRigidbody(sf::Vector2f(0, 1));

    // Pente trop raide -> faire chuter l'object
    if (PenteAngle > Rb->MaxAnglePente)
    {
        GetOwner()->AddWorldPosition(Hit.Normal * Hit.CancelDistance);
    }
    else
    {

        GetOwner()->AddWorldPosition(sf::Vector2f(0, -1) * Hit.CancelDistance);

        // Si l'angle est inférieur à 90 degree, c'est une pente descendante
        if (ObjectToPenteAngle <= 90)
        {
            if (Rb->GetVelocity().x < 0)
                Move = Vector::RotateVector(Hit.Normal, -90);
            else if (Rb->GetVelocity().x > 0)
                Move = Vector::RotateVector(Hit.Normal, 90);
        }
        else
        {
            if (Rb->GetVelocity().x < 0)
                Move = Vector::RotateVector(Hit.Normal, -90);
            else if (Rb->GetVelocity().x > 0)
                Move = Vector::RotateVector(Hit.Normal, 90);
        }
        Rb->AddForce(Move);
    }
}

// PRIVATE
void ICollider::CallCallbacks(ECollisionEvent CollisionEvent, GameObject *GameObjectHited)
{
    for (auto Callback : Callbacks[CollisionEvent])
        Callback(GameObjectHited);
}
