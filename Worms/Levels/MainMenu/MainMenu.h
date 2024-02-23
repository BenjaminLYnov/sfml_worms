#pragma once

#include "Level/Level.h"

class Worm;

class MainMenu : public Level
{
public:
    MainMenu();

    void Start() override;
    void Update(const float DeltaTime) override;

private:
    std::shared_ptr<Worm> MainWorm;

    void Toto();
};
