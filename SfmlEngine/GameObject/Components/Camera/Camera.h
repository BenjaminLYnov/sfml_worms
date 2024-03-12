#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclure la classe de vecteur de SFML

namespace sf
{
    class View;
    class RenderWindow;
}

class Camera : public IComponent
{
public:
    Camera();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    void SetWindow(sf::RenderWindow *_Window = nullptr);
    void SetEnabled(const bool bEnable);
    void SetFollowOwner(const bool bVal);
    void SetTargetViewCenter(const sf::Vector2f NewViewCenter);
    void SetCurrentViewCenter(const sf::Vector2f NewViewCenter);
    
    void SetZoom(const float _Zoom);
    float GetZoom() const;
    void AddZoom(const float Val);
    void ResetViewport();

    sf::Vector2f GetViewportCenter() const;

    void MoveView(const sf::Vector2f Move);

    // Position initiale de la vue
    sf::Vector2f TargetViewCenter = sf::Vector2f(0, 0);
    sf::Vector2f CurrentViewCenter = sf::Vector2f(0, 0);
    sf::Vector2f Offset = sf::Vector2f(0, 0);

    // Lag
    bool bEnableLag = false;
    float LagSpeed = 10;

protected:
    virtual void UpdateViewport(const float DeltaTime);
    virtual void FollowOwner(const float DeltaTime);

private:
    sf::RenderWindow *Window = nullptr;
    std::shared_ptr<sf::View> Viewport;

    bool bEnabled = true;
    bool bFollowOwner = true;

    float ZoomFactor = 1;

    // Fonction d'interpolation linéaire entre deux points
    sf::Vector2f Interpolate(const sf::Vector2f &p0, const sf::Vector2f &p1, float t);
};

#endif