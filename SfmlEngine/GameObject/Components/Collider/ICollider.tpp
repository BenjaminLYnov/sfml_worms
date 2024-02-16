#include "ICollider.h"

template <typename T, typename Method, typename... Args>
void ICollider::AddCallback(ECollisionEvent CollisionEvent,T *Obj, Method MethodToBind, Args... args)
{
    Callback Callback = std::bind(MethodToBind, Obj, args...);
    Callbacks[CollisionEvent].push_back(Callback);
}
