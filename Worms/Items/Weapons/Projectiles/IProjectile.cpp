#include "IProjectile.h"

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"

#include "GameObject/Components/Input/InputAction/InputAction.h"
#include "GameObject/Components/Input/InputAction/Key/Key.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include <Resources/Resources.h>

#include "Deleguate.h"

IProjectile::IProjectile()
{
    DeleguateOnDestroy = std::make_shared<Deleguate>();
}

void IProjectile::Start()
{
    Item::Start();
}

void IProjectile::Update(const float DeltaTime)
{
    Item::Update(DeltaTime);
}

void IProjectile::AddForce(const sf::Vector2f &Force)
{
}

void IProjectile::Destroy(GameObject *GameObjectToDestroy)
{
    DeleguateOnDestroy->Broadcast();
    Item::Destroy(GameObjectToDestroy);
}

void IProjectile::OnCollisionEnter(GameObject *GameObjectHited)
{
}
