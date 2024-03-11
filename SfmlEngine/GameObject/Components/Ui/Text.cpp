#include "Text.h"
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "GameObject/GameObject.h"

Text::Text(const unsigned char *Data, size_t Size)
{
    FontText = std::make_shared<sf::Font>();
    TextElement = std::make_shared<sf::Text>();

    if (!FontText->loadFromMemory(Data, Size))
    {
        std::cout << "failed to load font text\n";
    }

    TextElement->setFont(*FontText);
    TextElement->setCharacterSize(24);
}

void Text::Start()
{
}

void Text::Update(const float DeltaTime)
{
}

void Text::Render(sf::RenderWindow &Window)
{
    Window.draw(*TextElement);
}

void Text::UpdatePosition()
{
    sf::Vector2f NewPosition = GetOwner()->GetWorldPosition() + GetOwner()->GetRelativePosition() + Offset;
    TextElement->setPosition(NewPosition);
}

void Text::SetString(const std::string Value)
{
    TextElement->setString(Value);
    // Calculate the position to center the text
    sf::FloatRect TextBounds = TextElement->getLocalBounds();
    TextElement->setOrigin(TextBounds.left + TextBounds.width / 2.0f, TextBounds.top + TextBounds.height / 2.0f);
}

void Text::SetCharacterSize(const int Value)
{
    TextElement->setCharacterSize(Value);
}

void Text::SetFillColor(const sf::Color &Color = sf::Color::White)
{
    TextElement->setFillColor(Color);
}