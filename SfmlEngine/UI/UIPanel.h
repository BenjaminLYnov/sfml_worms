#pragma once
#include "UIElement.h"

enum class UILayout
{
    None,
    List
};

enum class UIDirection
{
    Horizontal,
    Vertical,
    None
};

enum class UIAlignment
{
    None,
    Start,
    Center,
    End,
    SpaceBetween
};

class UIPanel : public UIElement
{
    
protected:
    UILayout layout = UILayout::None;
    UIDirection direction = UIDirection::None;
    UIAlignment horizontal = UIAlignment::None;
    UIAlignment vertical = UIAlignment::None;

    void UpdateLayoutList();
    
public:
    UIPanel(const Vec2f& _pos, const Vec2f& _size);
    virtual const sf::FloatRect& UpdateRect(const sf::FloatRect& _parentRect);
    virtual void Draw(sf::RenderWindow& _window) override;

    UILayout GetLayout() const { return layout; }
    UIDirection GetDirection() const { return direction; }
    
    void SetLayout(UILayout _layout, UIDirection _direction){ layout = _layout; direction = _direction; }
    void SetHorizontalAlignment(UIAlignment _align) { horizontal = _align; }
    void SetVerticalAlignment(UIAlignment _align) { vertical = _align; }

    UIAlignment GetHorizontalAlignment() const { return horizontal; }
    UIAlignment GetVerticalAlignment() const { return vertical; }
    
};
