#pragma once
#include "UIElement.h"

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
    sf::Text textObj;
    sf::Font font;
    int fontSize;
};
