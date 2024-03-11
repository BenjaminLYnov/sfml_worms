#include "Deleguate.h"

void Deleguate::Broadcast()
{
    for (auto &CallbackToCall : Callbacks)
        CallbackToCall();
}