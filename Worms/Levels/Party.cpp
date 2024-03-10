#include "Party.h"
#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Shapes/Triangle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"
#include "GameObject/Components/Camera/Camera.h"
#include <SFML/Graphics/RectangleShape.hpp> // Assurez-vous d'inclure la bonne bibliothèque pour les formes SFML
#include <SFML/Graphics/ConvexShape.hpp>	// Assurez-vous d'inclure la bonne bibliothèque pour les formes SFML
#include "Levels/Graph/Graph.h"
#include "Levels/Graph/Cell.h"
#include "GameManager/GameManager.h"
#include "iostream"

Party::Party()
{
}

void Party::Start()
{
	GameObjects.clear();

    CurrentWorm.reset();

	G = std::make_shared<Graph>();
	G->World = this;
	G->Init();
	G->EnableCellsCollision(true);

	// Instance Main Character
	InitPlayers();

	Level::Start();

	// std::cout << G->Cells[G->Cells.size() - 1]->GetWorldPosition().x << "\n";
}

void Party::Update(const float DeltaTime)
{
	Level::Update(DeltaTime);
}

void Party::SwitchCharacter()
{
	if (!CurrentWorm)
		return;

	// Récupère tous les worms du level
	std::vector<std::shared_ptr<Worm>> Worms = GetAllGameObjectByClass<Worm>();

	for (size_t i = 0; i < Worms.size(); i++)
	{
		if (CurrentWorm == Worms[i])
		{

			std::shared_ptr<Worm> NextWorm;
			if (i + 1 < Worms.size())
			{
				NextWorm = Worms[i + 1];
			}
			else
			{
				NextWorm = Worms[0];
			}

			CurrentWorm->CameraComponent->SetWindow(nullptr);

			const sf::Vector2f CurrentViewCenter = CurrentWorm->CameraComponent->CurrentViewCenter;

			CurrentWorm = NextWorm;

			SetCharacterControlled(CurrentWorm);

			CurrentWorm->bCanFire = true;
			CurrentWorm->bCanMove = true;
			CurrentWorm->CameraComponent->SetWindow(GetWindow());
			CurrentWorm->CameraComponent->CurrentViewCenter = CurrentViewCenter;
			CurrentWorm->CameraComponent->bEnableLag = true;

			break;
		}
	}

	GM->LoadLevel("GraphEdition");
}

// PROTECTED

void Party::InitPlayers()
{
	for (int i = 0; i < NbPlayer; i++)
	{
		std::shared_ptr<Worm> NewWorm = std::make_shared<Worm>();
		NewWorm->SetName("Worm " + std::to_string(i));
		NewWorm->DeleguateActionDone->AddCallback(this, &Party::SwitchCharacter);
		AddGameObject(NewWorm);
		NewWorm->SetWorldPosition(sf::Vector2f(100 * i, 00));

		if (!CurrentWorm)
			CurrentWorm = NewWorm;
	}

	if (!CurrentWorm)
	{
		std::cout << "toto\n";
		return;
	}

	SetCharacterControlled(CurrentWorm);
	CurrentWorm->bCanFire = true;
	CurrentWorm->bCanMove = true;
	CurrentWorm->CameraComponent->SetWindow(GetWindow());
	CurrentWorm->CameraComponent->bEnableLag = true;

}

void Party::SpawnWorm(std::shared_ptr<Worm> WormToSpawn)
{
}
