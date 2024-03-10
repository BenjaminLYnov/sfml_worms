#ifndef PARTY_H
#define PARTY_H

#pragma once

#include "Level/Level.h"

class Worm;
class Graph;

class Party : public Level
{
public:
    Party();

    void Start() override;
    void Update(const float DeltaTime) override;

    void SwitchCharacter();

protected:
    void InitPlayers();
    virtual void SpawnWorm(std::shared_ptr<Worm> WormToSpawn);

private:
    const int NbPlayer = 2;

    std::shared_ptr<Worm> CurrentWorm;
    std::shared_ptr<Graph> G;

};

#endif