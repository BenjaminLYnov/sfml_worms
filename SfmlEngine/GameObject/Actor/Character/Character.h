#pragma once

#include "../Actor.h"
#include "./Animations/CharacterRun.h"

class StateMode;
class CharacterRun;

class Character : public Actor
{
public:
    Character();


protected:

    std::vector<std::shared_ptr<StateMode>> StateModeComponent;

    std::vector<std::shared_ptr<CharacterRun>> CharacterRun;

};
