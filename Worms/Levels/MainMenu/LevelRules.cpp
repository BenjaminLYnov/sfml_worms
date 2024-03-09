#include "LevelRules.h"

#include <iostream>

#include "Deleguate.h"
#include "../../../build/Worms/UIConstructor.h"
#include "Characters/Worm/Worm.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "Levels/UIConstructor.h"
#include "UI/Canvas.h"

#include "iostream"

LevelRules::LevelRules()
{
	// Instance Main Character
	InitPlayers();

	// Shapes
	/*std::shared_ptr<Square> Square1 = std::make_shared<Square>();
	Square1->SetWorldPosition(sf::Vector2f(400, 400));
	Square1->SquareColliderComponent->SetSize(sf::Vector2f(700, 200));
	Square1->SquareColliderComponent->SetMobility(EMobility::Stationary);
	AddGameObject(Square1);*/

	LevelRules::SetupUI();
	Square1->SquareColliderComponent->SetSize(sf::Vector2f(800, 100));
	Square1->SquareColliderComponent->SetMobility(EMobility::Static);
	AddGameObject(Square1);

	std::shared_ptr<Square> Square2 = std::make_shared<Square>();
	Square2->SetWorldPosition(sf::Vector2f(400, 250));
	Square2->SquareColliderComponent->SetSize(sf::Vector2f(300, 20));
	Square2->SquareColliderComponent->SetMobility(EMobility::Static);
	// AddGameObject(Square2);

	std::shared_ptr<Square> Square3 = std::make_shared<Square>();
	Square3->SetWorldPosition(sf::Vector2f(0, 300));
	Square3->SquareColliderComponent->SetSize(sf::Vector2f(300, 20));
	Square3->SquareColliderComponent->SetMobility(EMobility::Static);
	// AddGameObject(Square3);
}

void LevelRules::Start()
{
	Level::Start();
}

void LevelRules::Update(const float DeltaTime)
{
	Level::Update(DeltaTime);
}

void LevelRules::SwitchCharacter()
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

			CurrentWorm = NextWorm;

			CurrentWorm->bCanFire = true;
			CurrentWorm->bCanMove = true;


			SetCharacterControlled(CurrentWorm);

			break;
		}
	}
}

void LevelRules::SetupUI()
{
	Level::SetupUI();

	std::shared_ptr<UIConstructor> UI = std::make_shared<UIConstructor>();
	
	AddCanvas(UI->CreateTopCanvas());
	AddCanvas(UI->CreateDownCanvas());
	
	PlayerInfos* Player1Infos = UI->GetPlayer1Infos();
	PlayerInfos* Player2Infos = UI->GetPlayer2Infos();
	
	Player1Infos->UpdateName("SexyWorm");
	Player1Infos->UpdateHealth(10);
	
	Player2Infos->UpdateName("SexyWorm2");
	Player2Infos->UpdateHealth(20);
}

// PROTECTED

void LevelRules::InitPlayers()
{
	for (int i = 0; i < NbPlayer; i++)
	{
		std::shared_ptr<Worm> NewWorm = std::make_shared<Worm>();
		NewWorm->SetName("Worm" + i);
		NewWorm->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);
		AddGameObject(NewWorm);
		NewWorm->SetWorldPosition(sf::Vector2f(100 * i, 300));

		if (!CurrentWorm)
			CurrentWorm = NewWorm;
	}

	if (!CurrentWorm)
		return;

	SetCharacterControlled(CurrentWorm);

	CurrentWorm->bCanFire = true;
	CurrentWorm->bCanMove = true;
}
