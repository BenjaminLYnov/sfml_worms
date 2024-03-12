#ifndef TEXT_H
#define TEXT_H

#pragma once

#include <memory>
#include "./../IComponent.h"
#include <string>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Font;
    class Text;
    class Color;
}

class Text : public IComponent
{
public:
    Text(const unsigned char *Data = nullptr, size_t Size = 0);

    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Render(sf::RenderWindow &Window) override;
    virtual void UpdatePosition() override;

    void SetString(const std::string Value);
    void SetCharacterSize(const int Value);
    void SetFillColor(const sf::Color &Color);
    void SetWorldPosition(const sf::Vector2f Position);

    sf::Vector2f Offset;
    
private:
    std::shared_ptr<sf::Font> FontText;
    std::shared_ptr<sf::Text> TextElement;

};

#endif