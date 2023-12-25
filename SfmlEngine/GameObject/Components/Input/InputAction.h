#pragma once

#include <memory>
#include <vector>
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

  virtual void AddAction(ETriggerEvent &TriggerEvent, const Callback &Callback);
  virtual void Update(const float DeltaTime);

protected:
  virtual void AddKey(sf::Keyboard::Key NewKey);

  std::vector<Callback> TEStart;
  std::vector<Callback> TECompleted;
  std::vector<Callback> TETriggered;

  std::vector<sf::Keyboard::Key> Keys;
};
