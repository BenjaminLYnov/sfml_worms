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

	virtual void SetupUI() override;

private:
	std::vector<std::shared_ptr<Worm>> Worms;

};
