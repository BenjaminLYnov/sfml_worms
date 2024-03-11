#include "Item.h"

Item::Item() : GameObject()
{
}

void Item::Start()
{
    GameObject::Start();
}

void Item::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}

void Item::SetOwner(GameObject *_Owner)
{
    Owner = _Owner;
}

GameObject *Item::GetOwner()
{
    return Owner;
}