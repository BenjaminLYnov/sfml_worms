#include "Key.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include "Math/Vector/Vector.h"
#include "iostream"
#include <algorithm> // Pour std::clamp

bool Key::IsKeyPressed(const Keyboard &Button)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(Button));
}
bool Key::IsKeyPressed(const Mouse &Button)
{
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(Button));
}

bool Key::IsKeyPressed(unsigned int joystickId, const Joystick &Button)
{
    return sf::Joystick::isButtonPressed(joystickId, static_cast<unsigned int>(Button));
}

sf::Vector2f Key::GetAxisValue(const Joystick &Button)
{
    sf::Vector2f AxisValue(0, 0);

    unsigned int JoystickIndex = 0;

    switch (Button)
    {
    case Joystick::LStickAxis:
        AxisValue.x = sf::Joystick::getAxisPosition(JoystickIndex, sf::Joystick::X);
        AxisValue.y = sf::Joystick::getAxisPosition(JoystickIndex, sf::Joystick::Y);
        break;
    case Joystick::RStickAxis:
        AxisValue.x = sf::Joystick::getAxisPosition(JoystickIndex, sf::Joystick::U);
        AxisValue.y = sf::Joystick::getAxisPosition(JoystickIndex, sf::Joystick::V);
        break;
    }

    return AxisValue;
}

bool Key::IsUsingStick(const Joystick &Button)
{
    if (!KeyIsStickAxis(Button))
        return false;

    const float Deadzone = 15.0f; // Deadzone

    sf::Vector2f AxisValue = GetAxisValue(Button);
    return std::abs(AxisValue.x) > Deadzone || std::abs(AxisValue.y) > Deadzone;
}

bool Key::KeyIsStickAxis(const Joystick &Button)
{
    return Button == JoystickButtons::LStickAxis || Button == JoystickButtons::RStickAxis;
}

float Key::GetMagnitude(const sf::Vector2f Value)
{
    float Magnitude = sqrt(Value.x * Value.x + Value.y * Value.y);
    Magnitude = std::clamp(Magnitude, 0.f, 100.f);
    return Magnitude;
}