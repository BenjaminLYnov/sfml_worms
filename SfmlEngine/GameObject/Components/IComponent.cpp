#include "IComponent.h"


void IComponent::Start()
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::Update(const float DeltaTime)
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::Render(sf::RenderWindow &Window)
{
}

void IComponent::Enable()
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::Disable()
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::SetOwner(GameObject *Owner)
{
    this->Owner = Owner;
}

GameObject *IComponent::GetOwner() const
{
    return Owner;
}
