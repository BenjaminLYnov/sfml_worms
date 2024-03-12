#include "IComponent.h"
#include "../GameObject.h"

void IComponent::Start()
{
}

void IComponent::Update(const float DeltaTime)
{
}

void IComponent::UpdatePosition()
{
}

void IComponent::Render(sf::RenderWindow &Window)
{
}

void IComponent::SetOwner(GameObject *Owner)
{
    this->Owner = Owner;
}

GameObject *IComponent::GetOwner()
{
    return Owner;
}
