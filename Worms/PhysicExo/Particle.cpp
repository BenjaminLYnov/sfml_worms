#include "Particle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"

#include <iostream>

Particle::Particle()
{
    SquareColliderComponent = std::make_shared<SquareCollider>();
    RigidbodyComponent = std::make_shared<Rigidbody>();
    

    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    SetWorldPosition(sf::Vector2f(500, 10));
    SetName("Particule Test");
}

Particle::~Particle()
{
}

void Particle::Start()
{
    GameObject::Start();
}

void Particle::Update(const float DeltaTime)
{
    GameObject::Update(DeltaTime);
}

void Particle::Render(sf::RenderWindow &Window) const
{
    GameObject::Render(Window);
}
