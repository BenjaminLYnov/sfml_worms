#include "Rigidbody.h"
#include "iostream"
#include "GameObject/GameObject.h"

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
    AddForce(Gravity * GravityScale * DeltaTime);

    // Résistance de l'air appliquée à la vitesse verticale
    sf::Vector2f AirResistanceAccumulation = -AirResistance * sf::Vector2f(0, Velocity.y) * DeltaTime;

    // Appliquer la résistance de l'air
    AddForce(AirResistanceAccumulation);

    // Frottement horizontal pour décélérer la vitesse horizontale
    sf::Vector2f HorizontalDragAccumulation = -HorizontalDrag * sf::Vector2f(Velocity.x, 0) * DeltaTime;
    AddForce(HorizontalDragAccumulation);

    // Frottement vertical pour décélérer la vitesse vertical
    sf::Vector2f VerticalDragAccumulation = -VerticalDrag * sf::Vector2f(0, Velocity.y) * DeltaTime;
    AddForce(VerticalDragAccumulation);

    // Appliquer les forces accumulées pour mettre à jour la vitesse
    Velocity += ForceAccumulator * DeltaTime;

    // Limiter la vitesse à la vitesse terminale pour la chute
    if (Velocity.y > TerminalVelocity)
        Velocity.y = TerminalVelocity;

    // Réinitialiser les forces accumulées après leur application
    ForceAccumulator = sf::Vector2f(0, 0);

    // Mettre à jour la position en fonction de la vitesse
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + Velocity * DeltaTime;
    GetOwner()->SetWorldPosition(NewPosition);

    // Arrête complètement le mouvement horizontal et/ou vertical si la vitesse est très faible pour éviter le "drifting"
    if (std::abs(Velocity.x) < 0.1)
        Velocity.x = 0;
    if (std::abs(Velocity.y) < 0.1)
        Velocity.y = 0;


}

void Rigidbody::AddForce(const sf::Vector2f &Force)
{
    ForceAccumulator += Force;
}

void Rigidbody::SetVelocity(const sf::Vector2f &NewVelocity)
{
    Velocity = NewVelocity;
}

void Rigidbody::ResetVelocity()
{
    Velocity = sf::Vector2f(0, 0);
}

sf::Vector2f Rigidbody::GetVelocity() const
{
    return Velocity;
}

