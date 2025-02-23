#ifndef PARTY_H
#define PARTY_H

#pragma once

#include "Level/Level.h"

class UIConstructor;
struct PlayerInfos;
class Worm;
class Graph;
class Team;
class DeadZone;
class Text;
class Sound;

namespace sf
{
    class RenderWindow;
}

class Party : public Level
{
public:
    Party();

    void Start() override;
    void Update(const float DeltaTime) override;
    void Render(sf::RenderWindow &Window) const override;

    void SetupUI();

    std::shared_ptr<PlayerInfos> Player1Infos;
    std::shared_ptr<PlayerInfos> Player2Infos;
    std::shared_ptr<UIConstructor> UI;

protected:
    void InitTeams();
    virtual void SpawnWorm(std::shared_ptr<Worm> WormToSpawn);
    void SwitchCharacter();

private:
    const int NbTeam = 2;
    bool bGameIsOver = false;

    std::shared_ptr<Text> TextEndParty;

    std::shared_ptr<Sound> SoundWin;
    std::shared_ptr<Sound> SoundMatchNull;

    std::vector<std::shared_ptr<Team>> Teams;
    std::shared_ptr<DeadZone> DZ;

    std::shared_ptr<Worm> CurrentWorm;
    std::shared_ptr<Team> CurrentTeam;
    std::shared_ptr<Graph> G;

    void UpdateCurrentWorm(std::shared_ptr<Worm> NewWorm);

    std::shared_ptr<Team> GetNextTeam();
    bool AllTeamAreDead() const;
    bool GameIsOver();

    // Wind
    sf::Vector2f WindForce = sf::Vector2f(0, 0);
    const float MaxWindForce = 15000;
    const float MinWindForce = 5000;
    void ApplyWindForceToRigidbody();
    void UpdateWindForce();

};

#endif