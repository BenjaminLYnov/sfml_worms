#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>

namespace sf
{
    class RenderWindow;
    class Color;
    class RectangleShape;
}

class ProgressBar
{
public:
    ProgressBar(float Width, float Height, sf::Color FillColor, sf::Color BackgroundColor);

    void SetProgress(float Value);
    void SetPosition(const sf::Vector2f Position);

    void Render(sf::RenderWindow &Window) const;

private:
    std::shared_ptr<sf::RectangleShape> Background;
    std::shared_ptr<sf::RectangleShape> Fill;
};

#endif