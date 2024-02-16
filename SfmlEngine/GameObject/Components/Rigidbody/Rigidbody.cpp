#include "Rigidbody.h"
#include "iostream"
#include "GameObject/GameObject.h"

const float AIR_RESISTANCE = 0.1f;     // Coefficient de résistance de l'air
const float TERMINAL_VELOCITY = 50.0f; // Vitesse terminale

Rigidbody::Rigidbody() : Velocity(0, 0), ForceAccumulator(0, 0)
{
}

void Rigidbody::Start()
{
}

void Rigidbody::Update(const float DeltaTime)
{
    if (Gravity.x == 0 && Gravity.y == 0)
        return;

    // Appliquer la gravité
    AddForce(Gravity);

    // // Appliquer les forces accumulées pour mettre à jour la vitesse
    // Velocity += ForceAccumulator * DeltaTime;

    // std::cout << Velocity.y << "\n";

    sf::Vector2f airResistance = -AIR_RESISTANCE * Velocity;

    // Appliquer la résistance de l'air
    AddForce(airResistance);

    // Mettre à jour la vitesse
    Velocity += ForceAccumulator * DeltaTime;

    // Limiter la vitesse à la vitesse terminale
    if (Velocity.y > TERMINAL_VELOCITY)
    {
        Velocity.y = TERMINAL_VELOCITY;
    }

    ForceAccumulator = sf::Vector2f(0, 0);

    // Mettre à jour la position en fonction de la vitesse
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + Velocity * DeltaTime;
    GetOwner()->SetWorldPosition(NewPosition);
}

void Rigidbody::AddForce(const sf::Vector2f &Force)
{
    ForceAccumulator += Force;
}

void Rigidbody::SetVelocity(const sf::Vector2f &NewVelocity)
{
    Velocity = NewVelocity;
}

sf::Vector2f Rigidbody::GetVelocity() const
{
    return Velocity;
}
