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

    HitResult TestCollision(const SquareCollider &Other) const;

    virtual void CancelCollisionWith(const std::shared_ptr<SquareCollider> OtherCollider);
    virtual void CancelCollision(ICollider *Other) override;

    // Définit la taille du collider carré
    void SetSize(const sf::Vector2f &NewSize);

    // Obtient la taille du collider carré
    sf::Vector2f GetSize() const;
    sf::FloatRect GetRect() const;

    std::shared_ptr<sf::RectangleShape> Shape; // Représentation graphique du collider pour le rendu

protected:

private:
    sf::Vector2f Size; // Taille du collider carré

    sf::FloatRect Rect;
    sf::Vector2f getCenter(const sf::RectangleShape &shape) const;
    sf::Vector2f GetMoveAwayDirection(sf::RectangleShape &mover, const sf::RectangleShape &obstacle) const;

    float getCollisionResolutionDistance(const sf::RectangleShape &mover, const sf::RectangleShape &obstacle) const;
    sf::Vector2f GetCollisionResolutionVector(const sf::RectangleShape &Mover, const sf::RectangleShape &Obstacle) const;
    sf::Vector2f GetVectorNormal(const sf::RectangleShape &Mover, const sf::RectangleShape &Obstacle) const;



    bool RectangleShapeTestCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2) const;
    bool isPointInRotatedRect(const sf::Vector2f &point, const sf::RectangleShape &rect) const;

    std::array<sf::Vector2f, 4> GetTransformedCorners(const sf::RectangleShape &rect) const;
    float ProjectCornerOnAxis(const sf::Vector2f &corner, const sf::Vector2f &axis) const;
    sf::Vector2f Normalize(const sf::Vector2f &axis) const;
    std::pair<float, float> GetProjection(const std::array<sf::Vector2f, 4> &corners, const sf::Vector2f &axis) const;
    std::array<sf::Vector2f, 2> GetRectangleAxes(const std::array<sf::Vector2f, 4> &corners);
};