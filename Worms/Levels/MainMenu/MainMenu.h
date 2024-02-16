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
    void Enter();
    void Stay();
    void Exit();
    // void Exit(std::shared_ptr<Worm> w);

    std::shared_ptr<Worm> MainWorm;
};
