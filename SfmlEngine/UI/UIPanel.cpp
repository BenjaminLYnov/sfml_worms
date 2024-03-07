#include "UIPanel.h"

UIPanel::UIPanel(const Vec2f& _pos, const Vec2f& _size) : UIElement(_pos, _size)
{
}

const sf::FloatRect& UIPanel::UpdateRect(const sf::FloatRect& _parentRect)
{
    const sf::FloatRect& rect = UIElement::UpdateRect(_parentRect);

    if (layout == UILayout::List)
    {
        UpdateLayoutList();
    }

    return rect;
}


void UIPanel::Draw(sf::RenderWindow& _window)
{
    UIElement::Draw(_window);
}


void UIPanel::UpdateLayoutList()
{
    float totalWidth = GetTotalChildrenWidth();
    float totalHeight = GetTotalChildrenHeight();
    
    float currentX = 0;
    float currentY = 0;

    for(UIElement* child : childrenList)
    {
        if (direction == UIDirection::Horizontal)
        {
            switch(horizontal)
            {
                case UIAlignment::Start:
                {
                    child->SetPosX(currentX);
                    break;
                }
                case UIAlignment::Center:
                {
                    child->SetPosX((1 - totalWidth) / 2 + currentX);
                    break;
                }
                case UIAlignment::End:
                {
                    child->SetPosX(1 - totalWidth + currentX);
                    break;
                }
                case UIAlignment::SpaceBetween:
                {
                    float space = (1 - totalWidth) / (childrenList.size() - 1);
                    child->SetPosX(currentX);
                    currentX += space;
                    break;
                }
                
            }
            currentX += child->GetSize().x;
            switch (vertical)
            {
                case UIAlignment::Start:
                {
                    child->SetPosY(0);
                    break;
                }
                case UIAlignment::Center:
                {
                    child->SetPosY(0.5 - child->GetSize().y / 2);
                    break;
                }
                case UIAlignment::End:
                {
                    child->SetPosY(1 - child->GetSize().y);
                    break;
                }
            }
        }
        else if (direction == UIDirection::Vertical)
        {
            //TODO
        }
    }
}


