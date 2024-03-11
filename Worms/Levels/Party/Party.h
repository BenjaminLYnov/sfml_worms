#ifndef PARTY_H
#define PARTY_H

#pragma once

#include "Level/Level.h"

class Worm;
class Graph;
class Team;
class DeadZone;

class Party : public Level
{
public:
    Party();

    void Start() override;
    void Update(const float DeltaTime) override;


protected:
    void InitTeams();
    virtual void SpawnWorm(std::shared_ptr<Worm> WormToSpawn);
    void SwitchCharacter();

private:
    const int NbTeam = 2;

	std::vector<std::shared_ptr<Team>> Teams;
	std::shared_ptr<DeadZone> DZ;

    std::shared_ptr<Worm> CurrentWorm;
    std::shared_ptr<Team> CurrentTeam;
    std::shared_ptr<Graph> G;

    void UpdateCurrentWorm(std::shared_ptr<Worm> NewWorm);
    std::shared_ptr<Team> &GetNextTeam();
    bool AllTeamAreDead() const;

};

#endif