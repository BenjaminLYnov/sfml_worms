#pragma once
#include "Level/Level.h"

class Worm;

class LevelRules : public Level
{
public:
	LevelRules();

	void Start() override;
	void Update(const float DeltaTime) override;

	void SwitchCharacter();

protected:
	void InitPlayers();

	virtual void SetupUI() override;

private:
	std::shared_ptr<Worm> CurrentWorm;

	const int NbPlayer = 2;
}; 