#include "ICollider.h"
#include "../../GameObject.h"

ICollider::ICollider()
{
}

ICollider::~ICollider()
{
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

void ICollider::SetMobility(const EMobility NewMobility)
{
    Mobility = NewMobility;
}

ECollisionResponse ICollider::GetCollisionResponse() const
{
    return CollisionResponse;
}

void ICollider::SetCollisionResponse(const ECollisionResponse NewCollisionResponse)
{
    CollisionResponse = NewCollisionResponse;
}

//////////////////////////////////////////////////////
// PROTECTED

void ICollider::OnCollision(std::shared_ptr<ICollider> Other)
{
}

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

void ICollider::ManageCollisionResponses(GameObject *GameObjectHited, const bool bIsOnCollision)
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


// PRIVATE
void ICollider::CallCallbacks(ECollisionEvent CollisionEvent, GameObject *GameObjectHited)
{
    for (const auto Callback : Callbacks[CollisionEvent])
        Callback(GameObjectHited);
}
