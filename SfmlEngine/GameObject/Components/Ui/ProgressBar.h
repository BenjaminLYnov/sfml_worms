#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#pragma once

#include <memory>
#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace sf
{
    class RectangleShape;
    class Color;
}

class ProgressBar : public IComponent
{
public:
    ProgressBar();

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Render(sf::RenderWindow &Window) override;

    void SetWorldPosition(const sf::Vector2f Position);
    void SetSize(const sf::Vector2f Size);
    void SetFillColor(const sf::Color &Color = sf::Color::Red);
    void SetBackgroundColor(const sf::Color &Color = sf::Color::White);
    void SetProgress(const float Value);

private:
    float Progress = 50.0f;
    float MaxProgress = 100.0f;

    std::shared_ptr<sf::RectangleShape> ProgressBarBackgroundElement;
    std::shared_ptr<sf::RectangleShape> ProgressBarFillElement;
    std::shared_ptr<sf::Color> BackgroundColor;
    std::shared_ptr<sf::Color> FillColor;
};

#endif