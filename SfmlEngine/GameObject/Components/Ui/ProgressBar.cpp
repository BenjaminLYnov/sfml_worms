#include "ProgressBar.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameObject/GameObject.h"

ProgressBar::ProgressBar()
{
    ProgressBarBackgroundElement = std::make_shared<sf::RectangleShape>();
    ProgressBarFillElement = std::make_shared<sf::RectangleShape>();
}

void ProgressBar::Start()
{
}

void ProgressBar::Update(const float DeltaTime)
{
    ProgressBarFillElement->setSize(sf::Vector2f(ProgressBarBackgroundElement->getSize().x * (Progress / MaxProgress), ProgressBarBackgroundElement->getSize().y));
}

void ProgressBar::Render(sf::RenderWindow &Window)
{
    Window.draw(*ProgressBarBackgroundElement);
    Window.draw(*ProgressBarFillElement);
}

void ProgressBar::SetFillColor(const sf::Color &Color)
{
    ProgressBarFillElement->setFillColor(Color);
}

void ProgressBar::SetBackgroundColor(const sf::Color &Color)
{
    ProgressBarBackgroundElement->setFillColor(Color);
}

void ProgressBar::SetWorldPosition(const sf::Vector2f Position)
{
    ProgressBarBackgroundElement->setPosition(Position);
    ProgressBarFillElement->setPosition(Position);
}

void ProgressBar::SetSize(const sf::Vector2f Size)
{
    ProgressBarBackgroundElement->setSize(Size);
}

void ProgressBar::SetProgress(const float Value)
{
    Progress = Value;
    ProgressBarFillElement->setSize(sf::Vector2f(ProgressBarBackgroundElement->getSize().x * (Progress / MaxProgress), ProgressBarBackgroundElement->getSize().y));
}