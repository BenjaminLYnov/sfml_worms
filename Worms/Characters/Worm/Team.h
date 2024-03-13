#pragma once
#include <memory>
#include <vector>

#include "GameObject/GameObject.h"

class Worm;

class Team
{
public:
	Team(std::string _Name = "", const int NbWorms = 5);

	std::vector<std::shared_ptr<Worm>> GetWorms();
	std::shared_ptr<Worm> GetCurrentWorm();

	void UpdateToNextWorm();
	void UpdateToPreviousWorm();

	std::shared_ptr<Worm> GetPreviousWorm();
	std::shared_ptr<Worm> GetNextWorm();

	std::string GetName() const;
	void RemoveWorm(Worm *WormToRemove);

protected:
	std::shared_ptr<Worm> CurrentWorm;
	std::vector<std::shared_ptr<Worm>> Worms;

	std::string Name;

	virtual void InitWorms(const int NbWorms);
	virtual std::shared_ptr<Worm> CreateWorm(const std::string Name = "");
};
