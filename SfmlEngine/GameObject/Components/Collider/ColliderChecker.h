#pragma once
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include "HitResult.h"

struct ColliderChecker
{
    template <typename ColliderType>
    static HitResult TestCollision(const ColliderType &Collider1, const ColliderType &Collider2);
   

    template <typename ColliderType1, typename ColliderType2>
    static HitResult TestCollision(const ColliderType1 &Collider1, const ColliderType2 &Collider2);

 };
