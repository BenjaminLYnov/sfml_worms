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