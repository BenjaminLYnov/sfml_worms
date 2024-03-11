#include "Party.h"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"
#include "Characters/Worm/Team.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Shapes/Triangle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"
#include "GameObject/Components/Ui/Text.h"
#include "GameObject/Components/Camera/Camera.h"
#include <SFML/Graphics/RectangleShape.hpp> // Assurez-vous d'inclure la bonne bibliothèque pour les formes SFML
#include <SFML/Graphics/ConvexShape.hpp>	// Assurez-vous d'inclure la bonne bibliothèque pour les formes SFML
#include "Levels/Graph/Graph.h"
#include "Levels/Graph/Cell.h"
#include "GameManager/GameManager.h"
#include "iostream"
#include "Math/Random/RandomNumber.h"
#include "DeadZone.h"

Party::Party()
{
}

void Party::Start()
{
	GameObjects.clear();

	CurrentWorm.reset();
	CurrentTeam.reset();

	G = std::make_shared<Graph>();
	G->World = this;
	G->Init();
	G->EnableCellsCollision(true);

	DZ = std::make_shared<DeadZone>();
	DZ->SetWorldPosition(sf::Vector2f(0, 1000));
	AddGameObject(DZ);

	InitTeams();

	Level::Start();

	// std::cout << G->Cells[G->Cells.size() - 1]->GetWorldPosition().x << "\n";
}

void Party::Update(const float DeltaTime)
{
	Level::Update(DeltaTime);


}

// PROTECTED

void Party::InitTeams()
{
	Teams.clear();
	for (int i = 0; i < NbTeam; i++)
	{
		std::shared_ptr<Team> NewTeam = std::make_shared<Team>("Team " + std::to_string(i));
		Teams.push_back(NewTeam);

		if (!CurrentTeam)
			CurrentTeam = NewTeam;

		// Init Worms
		for (std::shared_ptr<Worm> W : NewTeam->GetWorms())
		{
			const float RandomNumberX = RandomNumber::RandomFloat(0, 1000);
			W->SetWorldPosition(sf::Vector2f(RandomNumberX, 0));
			W->DeleguateActionDone->AddCallback(this, &Party::SwitchCharacter);
			W->Team = NewTeam;

			AddGameObject(W);

			if (!CurrentWorm)
			{
				UpdateCurrentWorm(W);
			}
		}

		if (i > 0)
		{
			NewTeam->UpdateToPreviousWorm();
		}
	}
}

void Party::SpawnWorm(std::shared_ptr<Worm> WormToSpawn)
{
}

void Party::SwitchCharacter()
{
	if (!CurrentTeam || !CurrentWorm)
		return;

	if (Teams.size() == 0)
		return;

	// Vérifier si tous les worms sont mort
	if (AllTeamAreDead())
	{
		std::string WinMessage = "Match null !";
		std::cout << WinMessage << "\n";
		return;
	}

	CurrentTeam = GetNextTeam();

	// Vérifier si une team n'a plus aucun worm
	if (CurrentTeam->GetWorms().size() == 0)
	{
		// End Party
		std::string WinMessage = GetNextTeam()->GetName() + " a gagné la partie !";
		std::cout << WinMessage << "\n";
		return;
	}

	CurrentTeam->UpdateToNextWorm();
	UpdateCurrentWorm(CurrentTeam->GetCurrentWorm());
}

void Party::UpdateCurrentWorm(std::shared_ptr<Worm> NewWorm)
{
	if (!NewWorm)
		return;

	sf::Vector2f CurrentViewCenter = sf::Vector2f(0, 0);
	float CurrentZoom = 1;
	if (CurrentWorm)
	{
		CurrentWorm->TextName->SetFillColor(sf::Color::Red);
		CurrentWorm->CameraComponent->SetWindow();
		CurrentZoom = CurrentWorm->CameraComponent->GetZoom();
		CurrentViewCenter = CurrentWorm->CameraComponent->CurrentViewCenter;
	}
	else
	{
		CurrentViewCenter = NewWorm->GetWorldPosition();
	}

	CurrentWorm = NewWorm;
	CurrentWorm->bCanFire = true;
	CurrentWorm->bCanMove = true;
	CurrentWorm->bCanJump = true;
	CurrentWorm->CameraComponent->ResetViewport();
	CurrentWorm->CameraComponent->SetWindow(GetWindow());
	CurrentWorm->CameraComponent->SetCurrentViewCenter(CurrentViewCenter);
	CurrentWorm->CameraComponent->bEnableLag = true;
	CurrentWorm->CameraComponent->SetZoom(CurrentZoom);
	CurrentWorm->TextName->SetFillColor(sf::Color::Yellow);
	SetCharacterControlled(CurrentWorm);
}

std::shared_ptr<Team> &Party::GetNextTeam()
{
	for (int i = 0; i < Teams.size(); i++)
	{
		if (CurrentTeam == Teams[i])
		{
			if (i + 1 < Teams.size())
				return Teams[i + 1];
			else
				return Teams[0];
		}
	}

	return std::shared_ptr<Team>();
}

bool Party::AllTeamAreDead() const
{
	for (int i = 0; i < Teams.size(); i++)
	{
		if (Teams[i]->GetWorms().size() > 0)
			return false;
	}
	return true;
}
