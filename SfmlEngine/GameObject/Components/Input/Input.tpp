#include "Input.h"
#include "InputAction/InputAction.h"
#include <functional>
#include <type_traits>
#include <tuple>
#include "InputCallback.h"

template <typename T, typename Method>
void Input::BindAction(std::shared_ptr<InputAction> &IA, ETriggerEvent TriggerEvent, T *Obj, Method MethodToBind)
{
    InputCallback boundAction = MakeBoundAction(Obj, MethodToBind);
    AddInputAction(IA);
    IA->BindAction(TriggerEvent, boundAction);
}

////////////////////// 
// 


// Trait pour décomposer les types de fonctions
template <typename T>
struct function_traits;

// Spécialisation pour les fonctions membres
template <typename C, typename R, typename... Args>
struct function_traits<R (C::*)(Args...)>
{
    static const size_t nargs = sizeof...(Args); // Nombre d'arguments
};

// Spécialisation pour les fonctions membres const
template <typename C, typename R, typename... Args>
struct function_traits<R (C::*)(Args...) const>
{
    static const size_t nargs = sizeof...(Args); // Nombre d'arguments
};

// Fonction helper pour obtenir le nombre d'arguments
template <typename T>
constexpr size_t arg_count()
{
    return function_traits<T>::nargs;
}

template <typename T, typename Method>
InputCallback MakeBoundAction(T *obj, Method MethodToBind)
{
    if constexpr (arg_count<Method>() == 0)
    {
        return [obj, MethodToBind](sf::Vector2f)
        { std::invoke(MethodToBind, obj); };
    }
    else if constexpr (arg_count<Method>() == 1)
    {
        return [obj, MethodToBind](sf::Vector2f arg)
        { std::invoke(MethodToBind, obj, arg); };
    }
    else
    {
        static_assert(arg_count<MethodToBind>() <= 1, "MethodToBind cannot have more than one argument");
    }
}
