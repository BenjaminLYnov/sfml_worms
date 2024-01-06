// Callback.h
#ifndef CALLBACK_H
#define CALLBACK_H

#include <functional>
#include <SFML/System/Vector2.hpp>

using Callback = std::function<void(sf::Vector2f)>;

#endif // CALLBACK_H
