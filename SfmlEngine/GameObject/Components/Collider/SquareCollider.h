#pragma once

#include "ICollider.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML
#include <SFML/Graphics/Rect.hpp>

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

    virtual void UpdatePosition() override;

    virtual void OnCollision(std::shared_ptr<ICollider> Other) override;

    virtual bool IsOnCollision(std::shared_ptr<ICollider> Other) override; // Appelé lors d'un test de collision

    virtual void CancelCollisionWith(const std::shared_ptr<SquareCollider> OtherCollider);

    // Définit la taille du collider carré
    void SetSize(const sf::Vector2f &NewSize);

    // Obtient la taille du collider carré
    sf::Vector2f GetSize() const;
    sf::FloatRect GetRect() const;

protected:
private:
    sf::RectangleShape *Shape; // Représentation graphique du collider pour le rendu
    sf::Vector2f Size;         // Taille du collider carré

    sf::FloatRect Rect;

    sf::Vector2f GetVectorMoveToCancelCollision(sf::FloatRect OtherRect);
};
