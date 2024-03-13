#include "ProgressBar.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

ProgressBar::ProgressBar(float Width, float Height, sf::Color FillColor, sf::Color BackgroundColor)
{
    Background = std::make_shared<sf::RectangleShape>();
    Fill = std::make_shared<sf::RectangleShape>();

    Background->setSize(sf::Vector2f(Width, Height));
    Background->setFillColor(BackgroundColor);
    Background->setOrigin(Background->getSize().x / 2, Background->getSize().y / 2);

    Fill->setSize(sf::Vector2f(Width, Height));
    Fill->setFillColor(FillColor);
    Fill->setOrigin(Fill->getSize().x / 2, Fill->getSize().y / 2);
    SetProgress(0);
}

void ProgressBar::SetProgress(float Value)
{
    if (Value < 0.0f)
        Value = 0.0f;
    if (Value > 1.0f)
        Value = 1.0f;
    Fill->setSize(sf::Vector2f(Background->getSize().x * Value, Background->getSize().y));
}

void ProgressBar::SetPosition(const sf::Vector2f Position)
{
    Fill->setPosition(Position);
    Background->setPosition(Position);
}

void ProgressBar::Render(sf::RenderWindow &Window) const
{
    Window.draw(*Background);
    Window.draw(*Fill);
}
