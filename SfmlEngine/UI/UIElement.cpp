#include "UIElement.h"
#include <iostream>

UIElement::UIElement(const Vec2f& _pos, const Vec2f& _size) : pos(_pos), size(_size){}

void UIElement::InitResources()
{
    debugRectangle.setOutlineColor(sf::Color::Red);
    debugRectangle.setOutlineThickness(2);
    debugRectangle.setFillColor(sf::Color::Transparent);

    for(UIElement* child : childrenList)
        child->InitResources();
}

void UIElement::RemoveChild(UIElement* child)
{
    auto found = std::find(childrenList.begin(), childrenList.end(), child);
    if(found != childrenList.end())
    {
        childrenList.erase(found);
    }
}

void UIElement::Update(float dTime)
{
    for(UIElement* child : childrenList)
        child->Update(dTime);
}

const sf::FloatRect& UIElement::UpdateRect(const sf::FloatRect& parentRect)
{
    Vec2f vPos = Vec2f(parentRect.left, parentRect.top) + Vec2f(pos.x * parentRect.width, pos.y * parentRect.height);
    Vec2f vSize = Vec2f(parentRect.width * size.x, parentRect.height * size.y);

    renderRect.left = vPos.x;
    renderRect.top = vPos.y;

    renderRect.width = vSize.x;
    renderRect.height = vSize.y;

    if(drawDebug)
    {
        debugRectangle.setPosition(renderRect.left, renderRect.top);
        debugRectangle.setSize(sf::Vector2f(renderRect.width, renderRect.height));
    }

    switch(layout)
    {
        case UILayout::List:
        {
            UpdateLayoutList();
            break;
        }
    }

    for(UIElement* child : childrenList)
        child->UpdateRect(renderRect);

    return renderRect;
}

float UIElement::GetTotalChildrenWidth()
{
    float totalWidth = 0;
    for(UIElement* child : childrenList)
    {
        totalWidth += child->GetSize().x;
    }
    return totalWidth;
}

float UIElement::GetTotalChildrenHeight()
{
    float totalHeight = 0;
    for(UIElement* child : childrenList)
    {
        totalHeight += child->GetSize().y;
    }
    return totalHeight;
}

UIElement* UIElement::AddChild(UIElement* pChild)
{
    if (std::find(childrenList.begin(), childrenList.end(), pChild) == childrenList.end())
    {
        childrenList.push_back(pChild);
        return pChild;
    }
    return nullptr;
}

void UIElement::UpdateLayoutList()
{
}

void UIElement::Draw(sf::RenderWindow& window)
{
    if(drawDebug)
    {
        std::cout << "Drawing debug rectangle   +   " << debugRectangle.getSize().x << std::endl;
        window.draw(debugRectangle);
    }
        

    for(UIElement* child : childrenList)
        child->Draw(window);
}