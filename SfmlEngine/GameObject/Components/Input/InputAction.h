#pragma once

#include <functional>
#include <map>
#include <SFML/Window/Keyboard.hpp>

enum class ETriggerEvent;

// namespace sf
// {
//   class Keyboard;
// }

// namespace sf {
//     namespace Keyboard {
//         enum class Key; // Assuming Key is an enum class
//     }
// }

class InputAction
{
public:
    using Callback = std::function<void()>;

    InputAction() = default;
    virtual ~InputAction() = default;

    virtual void BindAction(ETriggerEvent TriggerEvent, const Callback &Callback);
    virtual void PollKeyEvents();

protected:
    virtual void AddKey(sf::Keyboard::Key NewKey);

    virtual void CallCallbacks(ETriggerEvent TriggerEvent);

    std::map<ETriggerEvent, std::vector<Callback>> Callbacks;

    std::vector<sf::Keyboard::Key> Keys;

private:
    // Variable pour suivre si la touche a déjà été traitée
    bool bIsKeyPressed = false;
};
