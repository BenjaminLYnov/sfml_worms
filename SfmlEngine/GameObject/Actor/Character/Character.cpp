#include "Character.h"
#include "GameObject/Components/Input/Input.h"

Character::Character() : Actor()
{
    InputComponent = std::make_shared<Input>();
    AddComponent(InputComponent);
}
