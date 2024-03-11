#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "GameObject/GameObject.h"
#include <iostream>

Camera::Camera()
{
    Viewport = std::make_shared<sf::View>(sf::FloatRect(0, 0, 800, 600));
}

void Camera::Start()
{
}

void Camera::Update(const float DeltaTime)
{
    if (!bEnabled)
        return;

    if (!Viewport)
        return;

    if (!Window)
        return;

    // Mise à jour de la position de la vue

    if (bFollowOwner)
        FollowOwner(DeltaTime);
    UpdateViewport(DeltaTime);
}

void Camera::SetWindow(sf::RenderWindow *_Window)
{
    Window = _Window;
}

void Camera::SetEnabled(const bool bEnable)
{
    bEnabled = bEnable;
}

void Camera::SetFollowOwner(const bool bVal)
{
    bFollowOwner = bVal;
}

void Camera::SetTargetViewCenter(const sf::Vector2f NewViewCenter)
{
    TargetViewCenter = NewViewCenter;
}

void Camera::SetCurrentViewCenter(const sf::Vector2f NewViewCenter)
{
    CurrentViewCenter = NewViewCenter;
}

void Camera::SetZoom(const float _Zoom)
{
    ZoomFactor = _Zoom;
}

void Camera::AddZoom(const float Val)
{
    ZoomFactor += Val;
}

float Camera::GetZoom() const
{
    return ZoomFactor;
}

void Camera::MoveView(const sf::Vector2f Move)
{
    TargetViewCenter += Move;
}

void Camera::ResetViewport()
{
    Offset = sf::Vector2f(0, 0);
}

// PROTECTED

void Camera::UpdateViewport(const float DeltaTime)
{
    if (!bEnableLag)
    {
        CurrentViewCenter = TargetViewCenter + Offset;
    }
    else
    {
        float Alpha = LagSpeed * DeltaTime;
        CurrentViewCenter = Interpolate(CurrentViewCenter, TargetViewCenter + Offset, Alpha);
    }

    Viewport->setCenter(CurrentViewCenter);

    // Limiter le niveau de zoom minimum
    if (ZoomFactor < 0.1f)
        ZoomFactor = 0.1f;

    // Limiter le niveau de zoom maximum
    if (ZoomFactor > 10.0f)
        ZoomFactor = 10.0f;

    Viewport->setSize(Window->getSize().x * ZoomFactor, Window->getSize().y * ZoomFactor);
    Window->setView(*Viewport);
}

void Camera::FollowOwner(const float DeltaTime)
{
    TargetViewCenter = GetOwner()->GetWorldPosition();
}

sf::Vector2f Camera::Interpolate(const sf::Vector2f &p0, const sf::Vector2f &p1, float t)
{
    return p0 + (p1 - p0) * t;
}
