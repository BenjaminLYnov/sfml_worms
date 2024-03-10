#pragma once
#include <memory>
#include <vector>

#include "GameObject/GameObject.h"

class Worm;

class Team
{
public:
	Team();
	~Team();

	//void GetNextCharacter();
	std::vector<std::shared_ptr<Worm>> Worms;
	std::shared_ptr<Worm> LastWorm;
	std::shared_ptr<Worm> GetNextWorm();


};
