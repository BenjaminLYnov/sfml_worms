#include "ICollider.h"

ICollider::ICollider()
{
}

ICollider::~ICollider()
{
}



void ICollider::SetOffset(const sf::Vector2f &NewOffset)
{
    Offset = NewOffset;
}


sf::Vector2f ICollider::GetOffset() const
{
    return Offset;
}
