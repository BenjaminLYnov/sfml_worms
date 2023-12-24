#pragma once

#include "ICollider.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML

// Forward declaration de sf::RectangleShape
namespace sf
{
    class RectangleShape;
}


class SquareCollider : public ICollider
{
public:
    SquareCollider(const sf::Vector2f InitialSize = sf::Vector2f(10, 10));
    
    ~SquareCollider() override; // Destructeur

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Render(sf::RenderWindow &Window) override;

    virtual void OnCollisionEnter(ICollider *Other) override;
    virtual void OnCollisionStay(ICollider *Other) override;
    virtual void OnCollisionExit(ICollider *Other) override;

    // Définit la taille du collider carré
    void SetSize(const sf::Vector2f &NewSize);

    // Obtient la taille du collider carré
    sf::Vector2f GetSize() const;

private:
    sf::RectangleShape *Shape; // Représentation graphique du collider pour le rendu
    sf::Vector2f Size; // Taille du collider carré
    
};
