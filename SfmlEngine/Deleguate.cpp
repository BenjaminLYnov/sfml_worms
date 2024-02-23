#include "Deleguate.h"

void Deleguate::Broadcast()
{
    for (auto &callback : Callbacks)
        callback(); // Exécution du callback
}