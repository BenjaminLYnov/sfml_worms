#include "ICollider.h"
#include "ColliderCallback.h"

template <typename T, typename Method>
void ICollider::AddCallback(ECollisionEvent CollisionEvent, T *Obj, Method MethodToBind)
{
    ColliderCallback Callback = [Obj, MethodToBind](GameObject *go)
    {
        // Convertit Method en fonction membre prenant GameObject* comme argument
        (Obj->*MethodToBind)(go);
    };

    Callbacks[CollisionEvent].push_back(Callback);
}