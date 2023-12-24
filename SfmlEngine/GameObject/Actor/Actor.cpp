#include "Actor.h"
#include "GameObject/Components/Collider/SquareCollider.h"

Actor::Actor() : GameObject()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    AddComponent(SquareColliderComponent);
}

// Pas d'implémentation des méthodes virtuelles pures ici
// Ces méthodes doivent être implémentées dans les sous-classes dérivées de Actor

