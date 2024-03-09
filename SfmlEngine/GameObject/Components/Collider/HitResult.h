#ifndef HITRESULT_H
#define HITRESULT_H

#pragma once

#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML

class HitResult
{
public:
    // HitResult(const bool _bIsOnCollision = false, const sf::Vector2f _Normal = sf::Vector2f(0, 0), const sf::Vector2f _CancelVector = sf::Vector2f(0, 0));
    HitResult(const bool _bIsOnCollision = false, const sf::Vector2f _Normal = sf::Vector2f(0, 0), const float _CancelDistance = 0);

    bool bIsOnCollision;
    sf::Vector2f Normal;
    // sf::Vector2f CancelVector;
    float CancelDistance;

private:
};

#endif