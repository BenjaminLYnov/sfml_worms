#include "Rigidbody.h"
#include "iostream"
#include "GameObject/GameObject.h"

const float AIR_RESISTANCE = 0.1f;      // Coefficient de résistance de l'air
const float TERMINAL_VELOCITY = 500.0f; // Vitesse terminale
const float HORIZONTAL_DRAG = 300.f; // Exemple de valeur, à ajuster selon les besoins
// const float HORIZONTAL_DRAG = 0.5f; // Exemple de valeur, à ajuster selon les besoins

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
    sf::Vector2f airResistance = -AIR_RESISTANCE * sf::Vector2f(0, Velocity.y) * DeltaTime;
    // Appliquer la résistance de l'air
    AddForce(airResistance);

    // Frottement horizontal pour décélérer la vitesse horizontale
    float horizontalDragFactor = HORIZONTAL_DRAG; // HORIZONTAL_DRAG est un facteur de frottement horizontal que vous définissez
    sf::Vector2f horizontalDrag = -horizontalDragFactor * sf::Vector2f(Velocity.x, 0) * DeltaTime;
    AddForce(horizontalDrag);

    // Appliquer les forces accumulées pour mettre à jour la vitesse
    Velocity += ForceAccumulator * DeltaTime;

    // Limiter la vitesse à la vitesse terminale pour la chute
    if (Velocity.y > TERMINAL_VELOCITY)
        Velocity.y = TERMINAL_VELOCITY;

    // Réinitialiser les forces accumulées après leur application
    ForceAccumulator = sf::Vector2f(0, 0);

    // Mettre à jour la position en fonction de la vitesse
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + Velocity * DeltaTime;
    GetOwner()->SetWorldPosition(NewPosition);

    // Optionnel : arrêtez complètement le mouvement horizontal si la vitesse est très faible pour éviter le "drifting"
    // if (std::abs(Velocity.x) < MINIMUM_VELOCITY_THRESHOLD)
    // {
    //     Velocity.x = 0;
    // }
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
