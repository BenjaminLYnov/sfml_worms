#pragma once

#include "../Actor.h"
#include "./Animations/CharacterRun.h"
#include "GameObject/Components/Input/Input.h"

class StateMode;
class CharacterRun;
// class Input;

class Character : public Actor
{
public:
    Character();


protected:

    std::shared_ptr<StateMode> StateModeComponent;
    std::shared_ptr<Input> InputComponent;

    std::vector<std::shared_ptr<CharacterRun>> CharacterRun;

};
