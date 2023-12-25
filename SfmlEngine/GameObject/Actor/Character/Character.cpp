#include "Character.h"
#include "GameObject/Components/Input/Input.h"

Character::Character() : Actor()
{
    InputComponent = std::make_shared<Input>();
    AddComponent(InputComponent);
}

std::shared_ptr<Input> Character::GetInputCOmpoennt()
{
    return InputComponent;
}