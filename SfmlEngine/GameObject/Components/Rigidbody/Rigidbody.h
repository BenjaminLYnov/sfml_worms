#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#pragma once

#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclure la classe de vecteur de SFML

class Rigidbody : public IComponent
{
public:
    Rigidbody();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    // Méthodes pour manipuler la physique
    void AddForce(const sf::Vector2f &Force);

    void SetVelocity(const sf::Vector2f &Velocity);
    void ResetVelocity();

    // Getters pour les propriétés physiques
    sf::Vector2f GetVelocity() const;
    sf::Vector2f GetPreviousPosition() const;
    sf::Vector2f GetCurrentPosition() const;
    void UpdatePreviousCurrentPosition();

    sf::Vector2f Gravity = sf::Vector2f(0, 5000);
    // sf::Vector2f Gravity = sf::Vector2f(0, 9.8f);

    float GravityScale = 20;
    float AirResistance = 0.1f;
    float TerminalVelocity = 500.0f;
    float HorizontalDrag = 300.0f;
    float VerticalDrag = 300.0f;
    float MaxAnglePente = 45.0f;

private:
    sf::Vector2f Velocity;         // Vitesse du Rigidbody
    sf::Vector2f ForceAccumulator; // Accumulateur de force pour les calculs de physique

    sf::Vector2f CurrentPosition;
    sf::Vector2f PreviousPosition;
};

#endif
