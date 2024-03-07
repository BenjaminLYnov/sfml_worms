#include "UIText.h"


UIText::UIText(const std::string& text, const sf::Font& _font, Vec2f _pos, Vec2f _size, int _fontSize, sf::Color _color, sf::Color _outlineColor)
    : UIElement(_pos, _size), text(text), color(_color), outlineColor(_outlineColor), font(_font), fontSize(_fontSize)
{
}

void UIText::InitResources()
{
    UIElement::InitResources();
    
    textObj.setString(text);
    textObj.setCharacterSize(fontSize);
    SetFont(font);
    SetColor(color, outlineColor);
}

sf::Vector2f round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

const sf::FloatRect& UIText::UpdateRect(const sf::FloatRect& _parentRect)
{
    const sf::FloatRect& rect = UIElement::UpdateRect(_parentRect);
    //set the position of the text at the center of the rectreturn rect;
    textObj.setOrigin(textObj.getLocalBounds().width / 2, textObj.getLocalBounds().height);
    textObj.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    
    return rect;
}

void UIText::Draw(sf::RenderWindow& _window)
{
    _window.draw(textObj);
    UIElement::Draw(_window);
}

void UIText::SetText(const std::string& _text)
{
    text = _text;
    textObj.setString(text);
}

void UIText::SetFont(const sf::Font& _font)
{
    textObj.setFont(_font);
}

void UIText::SetColor(const sf::Color& _color, const sf::Color& _outlineColor)
{
    color = _color;
    outlineColor = _outlineColor;
    textObj.setOutlineColor(outlineColor);
    textObj.setFillColor(color);
}
