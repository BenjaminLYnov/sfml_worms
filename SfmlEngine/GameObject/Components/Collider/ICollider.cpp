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

void ICollider::SetLayer(Layers NewLayers)
{
    Mask = NewLayers;
}

void ICollider::AddLayer(Layers LayersToAdd)
{
    Mask += LayersToAdd;
}

void ICollider::RemoveLayer(Layers LayersToRemove)
{
    Mask = ~Mask & LayersToRemove;
}

bool ICollider::HasLayer(Layers LayersToCheck)
{
    return (Mask & LayersToCheck);
}

char ICollider::GetMask() const
{
    return Mask;
}

void ICollider::CallCallbacks(ECollisionEvent CollisionEvent)
{
    for (const auto Callback : Callbacks[CollisionEvent])
        Callback();
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

void ICollider::OnCollision(std::shared_ptr<ICollider> Other)
{
    if (!Other)
        return;

    // Vérifier s'il y a collision
    const bool bIsOnCollision = IsOnCollision(Other);

    // S'il n'y pas collision
    if (!bIsOnCollision)
    {
        // S'il l'autre game object est déjà dans le tableau GameObjects, alors il vient de sortir de la collision
        if (HasGameObject(Other->GetOwner()))
        {
            // Enlève l'autre du tableau GameObjects
            RemoveGameObject(Other->GetOwner());

            // Appel des callbacks lors de l'exit
            CallCallbacks(ECollisionEvent::Exit);
        }
        return;
    }

    // Il y a collision

    // S'il l'autre game object n'est déjà dans le tableau GameObjects, alors il vient de rentrer en collision
    if (!HasGameObject(Other->GetOwner()))
    {
        // Ajoute l'autre au tableau GameObjects
        AddGameObject(Other->GetOwner());

        // Appel des callbacks lors de la collision
        CallCallbacks(ECollisionEvent::Enter);
    }

    // Appel des callbacks de tant qu'il y a collision
    CallCallbacks(ECollisionEvent::Stay);
}
