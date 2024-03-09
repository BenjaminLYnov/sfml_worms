#ifndef TRIANGLECOLLIDER_H
#define TRIANGLECOLLIDER_H

#pragma once
#include "ICollider.h"

namespace sf
{
    class ConvexShape;
}

class TriangleCollider : public ICollider
{
public:
    TriangleCollider(const sf::Vector2f Point1 = sf::Vector2f(0, 0), const sf::Vector2f Point2 = sf::Vector2f(10, 0), sf::Vector2f Point3 = sf::Vector2f(5, 10));
    ~TriangleCollider();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Render(sf::RenderWindow &Window) override;

    std::shared_ptr<sf::ConvexShape> Shape;

    HitResult TestCollision(const TriangleCollider &Other) const;
    virtual void CancelCollision(ICollider *Other) override;

    void SetPoints(const sf::Vector2f Point1, const sf::Vector2f Point2, sf::Vector2f Point3);

private:
    std::pair<float, float> projectPolygon(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &vertices) const;
    bool overlap(const std::pair<float, float> &projection1, const std::pair<float, float> &projection2) const;
    sf::Vector2f edgeNormal(const sf::Vector2f &start, const sf::Vector2f &end) const;
    bool checkCollision(const sf::ConvexShape &triangle1, const sf::ConvexShape &triangle2) const;

    // sf::Vector2f calculateSeparationVector(const sf::ConvexShape &triangle1, const sf::ConvexShape &triangle2) const;

};

#endif