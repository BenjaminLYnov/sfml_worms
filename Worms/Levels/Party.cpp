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

#include "iostream"

Party::Party(const int _NbPlayer) : NbPlayer(_NbPlayer)
{
}

void Party::Start()
{
	// Instance Main Character
	InitPlayers();

	// Shapes
	std::shared_ptr<Square> Square1 = std::make_shared<Square>();
	Square1->SetWorldPosition(sf::Vector2f(0, 400));
	// Square1->SquareColliderComponent->SetSize(sf::Vector2f(400, 100));
	Square1->SquareColliderComponent->SetSize(sf::Vector2f(2000, 10));
	// Square1->SquareColliderComponent->SetSize(sf::Vector2f(600, 100));
	// Square1->SquareColliderComponent->SetSize(sf::Vector2f(50, 50));
	// Square1->SquareColliderComponent->SetSize(sf::Vector2f(200, 50));
	Square1->SquareColliderComponent->SetMobility(EMobility::Static);
	// Square1->SquareColliderComponent->Shape->setRotation(-70);
	// Square1->SquareColliderComponent->Shape->setRotation(10);
	AddGameObject(Square1);

	std::shared_ptr<Circle> Circle1 = std::make_shared<Circle>();
	Circle1->SetWorldPosition(sf::Vector2f(400, 400));
	// Circle1->CircleColliderComponent->SetSize(sf::Vector2f(800, 100));
	// Circle1->CircleColliderComponent->SetSize(sf::Vector2f(50, 50));
	// Circle1->CircleColliderComponent->SetRadius(50);
	Circle1->CircleColliderComponent->SetMobility(EMobility::Static);
	// AddGameObject(Circle1);

	std::shared_ptr<Triangle> Triangle1 = std::make_shared<Triangle>();
	Triangle1->SetWorldPosition(sf::Vector2f(400, 400));
	// Triangle1->TriangleColliderComponent->SetSize(sf::Vector2f(800, 100));
	// Triangle1->TriangleColliderComponent->SetSize(sf::Vector2f(50, 50));
	Triangle1->TriangleColliderComponent->SetMobility(EMobility::Static);
	Triangle1->TriangleColliderComponent->SetPoints(sf::Vector2f(0, 0), sf::Vector2f(300, 0), sf::Vector2f(150, 200));
	// Triangle1->TriangleColliderComponent->Shape->rotate(70);
	Triangle1->TriangleColliderComponent->Shape->rotate(40);
	// Triangle1->TriangleColliderComponent->Shape->rotate(120);
	// AddGameObject(Triangle1);

	std::shared_ptr<Square> Square2 = std::make_shared<Square>();
	Square2->SetWorldPosition(sf::Vector2f(400, 340));
	// Square2->SquareColliderComponent->SetSize(sf::Vector2f(300, 20));
	Square2->SquareColliderComponent->SetSize(sf::Vector2f(20, 20));
	Square2->SquareColliderComponent->SetMobility(EMobility::Static);
	// AddGameObject(Square2);

	std::shared_ptr<Square> Square3 = std::make_shared<Square>();
	Square3->SetWorldPosition(sf::Vector2f(0, 300));
	Square3->SquareColliderComponent->SetSize(sf::Vector2f(300, 20));
	Square3->SquareColliderComponent->SetMobility(EMobility::Static);
	// AddGameObject(Square3);

	Level::Start();
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
		return;

	SetCharacterControlled(CurrentWorm);
	CurrentWorm->bCanFire = true;
	CurrentWorm->bCanMove = true;
	CurrentWorm->CameraComponent->SetWindow(GetWindow());
	CurrentWorm->CameraComponent->bEnableLag = true;
}
