#pragma once
#include "UIElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <memory>

namespace sf
{
    class Text;
    class Font;
    class RenderWindow;
}

class UIText : public UIElement
{
public:
    UIText(const std::string& text, const sf::Font& _font, Vec2f _pos, Vec2f _size, int _fontSize, sf::Color _color = sf::Color::White, sf::Color _outlineColor = sf::Color::Black);
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect) override;
    virtual void InitResources() override;
    virtual void Draw(sf::RenderWindow& _window) override;
    virtual void SetVisibility(bool _vis) override;
    virtual void SetGreyed(bool _greyed) override;

    void SetText(const std::string& _text);
    void SetFont(const sf::Font& _font);
    void SetColor(const sf::Color& _color, const sf::Color& _outlineColor);

protected:
    std::string text;
    sf::Color storedColor;
    sf::Color color;
    sf::Color outlineColor;
    std::shared_ptr<sf::Text> textObj;
    std::shared_ptr<sf::Font> font;
    int fontSize;
};
