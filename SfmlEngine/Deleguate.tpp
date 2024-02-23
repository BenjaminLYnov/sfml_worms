#include "Deleguate.h"

template <typename T, typename Method>
void Deleguate::AddCallback(T *Obj, Method MethodToBind)
{
    Callbacks.push_back([=](){ (Obj->*MethodToBind)(); });
}
