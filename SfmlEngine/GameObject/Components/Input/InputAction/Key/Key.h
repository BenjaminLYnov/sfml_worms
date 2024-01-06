#pragma once

#include "Buttons/JoystickButtons.h"
#include "Buttons/KeyboardButtons.h"
#include "Buttons/MouseButtons.h"

class Key
{
public:
    // Inclusion des Enum class des touches
    using Keyboard = KeyboardButtons;
    using Mouse = MouseButtons;
    using Joystick = JoystickButtons;

    // Méthodes statiques pour vérifier si une touche est pressée
    static bool IsKeyPressed(const Keyboard &Button);
    static bool IsKeyPressed(const Mouse &Button);
    static bool IsKeyPressed(unsigned int joystickId, const Joystick &Button);

    // Joystick Axis Fonctions
    static sf::Vector2f GetAxisValue(const Joystick &Button);
    static bool IsUsingStick(const Joystick &Button);
    static bool KeyIsStickAxis(const Joystick &Button);
    static float GetMagnitude(const sf::Vector2f Value);

private:

};
