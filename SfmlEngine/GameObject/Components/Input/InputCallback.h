#ifndef INPUTCALLBACK_H
#define INPUTCALLBACK_H

#pragma once

#include <functional>
#include <SFML/System/Vector2.hpp>

using InputCallback = std::function<void(sf::Vector2f)>;


#endif