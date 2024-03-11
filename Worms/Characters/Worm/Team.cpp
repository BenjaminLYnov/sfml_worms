#include "Team.h"
#include "Worm.h"
#include <iostream>

Team::Team(std::string _Name, const int NbWorms)
{
	Name = _Name;
	InitWorms(NbWorms);
	if (Worms.size() > 0)
		CurrentWorm = Worms[0];
}

std::vector<std::shared_ptr<Worm>> Team::GetWorms()
{
	return Worms;
}

std::shared_ptr<Worm> Team::GetCurrentWorm()
{
	return CurrentWorm;
}

void Team::UpdateToNextWorm()
{
	CurrentWorm = GetNextWorm();
}

void Team::UpdateToPreviousWorm()
{
	CurrentWorm = GetPreviousWorm();
}

std::shared_ptr<Worm> Team::GetNextWorm()
{
	if (!CurrentWorm)
		return std::shared_ptr<Worm>();

	if (Worms.size() == 1)
		return Worms[0];

	for (int i = 0; i < Worms.size(); i++)
	{
		if (!Worms[i].get())
			return std::shared_ptr<Worm>();

		if (CurrentWorm == Worms[i])
		{
			std::shared_ptr<Worm> NextWorm;
			if (i + 1 < Worms.size())
				NextWorm = Worms[i + 1];
			else
				NextWorm = Worms[0];
			return NextWorm;
		}
	}

	return CurrentWorm;
}

std::shared_ptr<Worm> Team::GetPreviousWorm()
{
	if (!CurrentWorm)
		return std::shared_ptr<Worm>();

	if (Worms.size() == 1)
		return Worms[0];

	for (int i = 0; i < Worms.size(); i++)
	{
		if (!Worms[i].get())
			return std::shared_ptr<Worm>();

		if (CurrentWorm == Worms[i])
		{
			std::shared_ptr<Worm> PreviousWorm;
			if (i - 1 > 0)
				PreviousWorm = Worms[i - 1];
			else
				PreviousWorm = Worms[Worms.size() - 1];

			return PreviousWorm;
		}
	}

	return CurrentWorm;
}

std::string Team::GetName() const
{
	return Name;
}

void Team::RemoveWorm(Worm *WormToRemove)
{

	// Parcourir le vecteur de Worms
	for (auto it = Worms.begin(); it != Worms.end(); ++it)
	{
		// Vérifier si le pointeur correspond au Worm à supprimer
		if ((*it).get() == WormToRemove)
		{
			if ((*it) == CurrentWorm && Worms.size() > 1)
			{
				CurrentWorm = GetPreviousWorm();
				std::cout << CurrentWorm->GetName() << "\n";
			}

			// Supprimer le Worm du tableau
			Worms.erase(it);
			break;
		}
	}
}

// PROTECTED

void Team::InitWorms(const int NbWorms)
{
	for (int i = 0; i < NbWorms; i++)
		Worms.push_back(CreateWorm(Name + " - Worm " + std::to_string(i)));
}

std::shared_ptr<Worm> Team::CreateWorm(const std::string Name)
{
	std::shared_ptr<Worm> NewWorm = std::make_shared<Worm>();
	NewWorm->SetName(Name);
	return NewWorm;
}
