#ifndef MOUSE_BUTTONS_H
#define MOUSE_BUTTONS_H

#pragma once

#include <SFML/Window/Mouse.hpp>

enum class MouseButtons {
    Left = sf::Mouse::Left,
    Right = sf::Mouse::Right,
    Middle = sf::Mouse::Middle,
    XButton1 = sf::Mouse::XButton1,
    XButton2 = sf::Mouse::XButton2,
};

#endif // MOUSE_BUTTONS_H
