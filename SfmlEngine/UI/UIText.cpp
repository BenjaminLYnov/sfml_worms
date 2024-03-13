#include "UIText.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

UIText::UIText(const std::string& text, const sf::Font& _font, Vec2f _pos, Vec2f _size, int _fontSize, sf::Color _color, sf::Color _outlineColor)
    : UIElement(_pos, _size), text(text), color(_color), outlineColor(_outlineColor), fontSize(_fontSize)
{
    textObj = std::make_shared<sf::Text>();
    font = std::make_shared<sf::Font>(_font);
}

void UIText::InitResources()
{
    UIElement::InitResources();
    
    textObj->setString(text);
    textObj->setCharacterSize(fontSize);
    SetFont(*font);
    SetColor(color, outlineColor);
}

const sf::FloatRect& UIText::UpdateRect(const sf::FloatRect& _parentRect)
{
    const sf::FloatRect& rect = UIElement::UpdateRect(_parentRect);
    //set the position of the text at the center of the rectreturn rect;
    textObj->setOrigin(textObj->getLocalBounds().width / 2, textObj->getLocalBounds().height);
    textObj->setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    
    return rect;
}

void UIText::Draw(sf::RenderWindow& _window)
{
    _window.draw(*textObj);
    UIElement::Draw(_window);
}

void UIText::SetVisibility(bool _vis)
{
    UIElement::SetVisibility(_vis);
    textObj->setFillColor(_vis ? storedColor : sf::Color::Transparent);
}

void UIText::SetGreyed(bool _greyed)
{
    UIElement::SetGreyed(_greyed);
    SetColor(_greyed ? sf::Color(100, 100, 100) : storedColor, outlineColor);
}

void UIText::SetText(const std::string& _text)
{
    text = _text;
    textObj->setString(text);
}

void UIText::SetFont(const sf::Font& _font)
{
    textObj->setFont(_font);
}

void UIText::SetColor(const sf::Color& _color, const sf::Color& _outlineColor)
{
    storedColor = color;
    color = _color;
    outlineColor = _outlineColor;
    textObj->setOutlineColor(outlineColor);
    textObj->setFillColor(color);
}
