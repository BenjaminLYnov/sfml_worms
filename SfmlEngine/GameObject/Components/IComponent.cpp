#include "IComponent.h"
#include "../GameObject.h"

IComponent::~IComponent()
{
}

void IComponent::Start()
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::Update(const float DeltaTime)
{
    // Implémentation par défaut (peut être vide)
}

void IComponent::UpdatePosition()
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
// void IComponent::SetOwner(std::shared_ptr<GameObject> Owner)
{
    // Conversion du pointeur brut en std::shared_ptr
    // std::shared_ptr<GameObject> SharedPointer(Owner);
    this->Owner = Owner;
    // this->Owner = SharedPointer;
}

GameObject *IComponent::GetOwner()
// std::shared_ptr<GameObject> IComponent::GetOwner()
{
    return Owner;
}
