// #pragma once
// #include "Level/Level.h"

// class Worm;
// class Team;

// class LevelRules : public Level
// {
// public:
// 	LevelRules();

// 	void Start() override;
// 	void Update(const float DeltaTime) override;

// 	void InitGrid();

// 	void SwitchCharacter();

// private:
// 	std::vector<std::shared_ptr<Team>> Teams;

// 	int NbTeams = 2;
// 	int NbWormsInTeam = 3;
// 	int CurrentTeamIndex = 0;
// 	int CurrentWormIndex = 0;


// private:
// 	std::shared_ptr<Worm> CurrentWorm;

// 	const int NbPlayer = 2;
// }; 