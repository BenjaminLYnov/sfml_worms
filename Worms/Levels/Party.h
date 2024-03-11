#ifndef PARTY_H
#define PARTY_H

#pragma once

#include "Level/Level.h"

class Worm;

class Party : public Level
{
public:
    Party(const int _NbPlayer = 2);

    void Start() override;
    void Update(const float DeltaTime) override;

    void SwitchCharacter();

protected:
    void InitPlayers();

private:
    std::shared_ptr<Worm> CurrentWorm;

    int NbPlayer;
};

#endif