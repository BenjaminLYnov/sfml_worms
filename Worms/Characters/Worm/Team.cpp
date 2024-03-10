#include "Team.h"

Team::Team()
{
	LastWorm = nullptr;
}

Team::~Team()
{
}

std::shared_ptr<Worm> Team::GetNextWorm()
{
	if(LastWorm == nullptr)
	{
		LastWorm = Worms[0];
		return LastWorm;
	}
	else
	{
		for(int i = 0; i < Worms.size(); i++)
		{
			if(Worms[i] == LastWorm)
			{
				if(i == Worms.size() - 1)
				{
					LastWorm = Worms[0];
					return LastWorm;
				}
				else
				{
					LastWorm = Worms[i + 1];
					return LastWorm;
				}
			}
		}
	}
	return nullptr;
}
