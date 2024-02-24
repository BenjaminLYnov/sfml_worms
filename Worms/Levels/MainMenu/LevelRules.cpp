#include "LevelRules.h"

#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

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
	AddGameObject(AnotherWorm);

	AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));
	SetCharacterControlled(MainWorm);
	MainWorm->bIsControlled = true;
	MainWorm->bCanFire = true;
	MainWorm->bCanMove = true;
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
	for(auto &Worm : Worms)
	{
		if(Worm->bIsControlled)
		{
			Worm->bIsControlled = false;
		}
		else
		{
			Worm->bIsControlled = true;
			Worm->bCanFire = true;
			Worm->bCanMove = true;
			SetCharacterControlled(Worm);
		}

	}
}
