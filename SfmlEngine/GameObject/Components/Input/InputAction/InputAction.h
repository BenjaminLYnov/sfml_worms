#pragma once

#include <map>
#include "../InputCallback.h"
#include "Axis.h"

class ActionKey;

enum class ETriggerEvent;

class InputAction
{
public:
    virtual ~InputAction() = default;

    virtual void BindAction(ETriggerEvent TriggerEvent, const InputCallback &Callback);
    virtual void PollKeyEvents();
    virtual void SetNeedKeyReleaseFirst(const bool _bNeedKeyReleaseFirst);
    

protected:
    virtual void AddKey(ActionKey NewActionKey, const bool bIsAxisKey = false, const Axis AxisType = Axis::Horizontal, const bool bNegateFlag = false);

private:
    std::map<ETriggerEvent, std::vector<InputCallback>> Callbacks;
    std::vector<ActionKey> ActionKeys;

    // Variable pour suivre si la touche a déjà été traitée
    bool bIsKeyPressed = false;

    bool bNeedKeyReleaseFirst = false;

    virtual void CallCallbacks(ETriggerEvent TriggerEvent, const sf::Vector2f Value = sf::Vector2f(0, 0));

    sf::Vector2f GetInputValue() const;

    bool KeyIsPressed() const;
    bool HasKey(const ActionKey &Key) const;
    bool AreKeysEqual(const ActionKey &Key1, const ActionKey &Key2) const;

    void SetActionKeyValue(const ActionKey &ActionKey, sf::Vector2f &InputValue) const;
};
