#include "LevelRules.h"

#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Components/Collider/SquareCollider.h"

LevelRules::LevelRules()
{
	// Instance Main Character
	std::shared_ptr<Worm> MainWorm = std::make_shared<Worm>();
	std::shared_ptr<Worm> AnotherWorm = std::make_shared<Worm>();

	Worms.push_back(MainWorm);
	Worms.push_back(AnotherWorm);

	MainWorm->SetName("p1");

	MainWorm->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);
	AnotherWorm->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);

	AnotherWorm->SetName("p2");

	AddGameObject(MainWorm);
	// AddGameObject(AnotherWorm.get());

	AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));
	SetCharacterControlled(MainWorm.get());
	MainWorm->bIsControlled = true;
	MainWorm->bCanFire = true;
	MainWorm->bCanMove = true;

	// Shapes
	std::shared_ptr<Square> Square1 = std::make_shared<Square>();
	Square1->SetWorldPosition(sf::Vector2f(400, 400));
	Square1->SquareColliderComponent->SetSize(sf::Vector2f(700, 200));
	Square1->SquareColliderComponent->SetMobility(EMobility::Stationary);
	AddGameObject(Square1);
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
	
	for (auto &Worm : Worms)
	{
		if (Worm->bIsControlled)
		{
			Worm->bIsControlled = false;
		}
		else
		{
			Worm->bIsControlled = true;
			Worm->bCanFire = true;
			Worm->bCanMove = true;
			SetCharacterControlled(Worm.get());
		}
	}
}
