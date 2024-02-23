#ifndef DELEGUATE_H
#define DELEGUATE_H

#pragma once

#include <functional>

class Deleguate
{
public:
    using Callback = std::function<void()>;

    Deleguate() = default;

    void Broadcast();

    template <typename T, typename Method>
    void AddCallback(T *Obj, Method MethodToBind);

private:
    std::vector<Callback> Callbacks;
};

#include "Deleguate.tpp"

#endif