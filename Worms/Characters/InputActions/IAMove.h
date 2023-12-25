#pragma once

#include "GameObject/Components/Input/InputAction.h"
#include <SFML/Window/Keyboard.hpp>

class IAMove : public InputAction
{
public:
    IAMove()
    {
        AddKey(sf::Keyboard::A);
    }
};
