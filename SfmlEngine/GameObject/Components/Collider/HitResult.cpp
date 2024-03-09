#include "HitResult.h"

HitResult::HitResult(const bool _bIsOnCollision, const sf::Vector2f _Normal, const float _CancelDistance) : bIsOnCollision(_bIsOnCollision),
                                                                                                            Normal(_Normal),
                                                                                                            CancelDistance(_CancelDistance)
{
}
