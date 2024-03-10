#include "LevelRules.h"

#include "Deleguate.h"
#include "Characters/Worm/Team.h"
#include "Characters/Worm/Worm.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "Math/Random/RandomNumber.h"

LevelRules::LevelRules()
{
	// Instance Main Character
	/*std::shared_ptr<Worm> MainWorm = std::make_shared<Worm>();
	std::shared_ptr<Worm> AnotherWorm = std::make_shared<Worm>();*/

	//create two teams
	for(int i = 0; i < NbTeams; i++)
	{
		std::shared_ptr<Team> Team1 = std::make_shared<Team>();
		Teams.push_back(Team1);
	}

 	//add the worms to the teams
	for(auto &Team : Teams)
	{
		for(int i = 0; i < NbWormsInTeam; i++)
		{
			std::shared_ptr<Worm> WormCharacter = std::make_shared<Worm>();
			Team->Worms.push_back(WormCharacter);
			WormCharacter->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);
		}
	}

	for(auto &Team : Teams)
	{
		for(auto &Worm : Team->Worms)
		{
			AddGameObject(Worm);
			//set random position
			const float RandomNumberX = RandomNumber::RandomFloat(0,1000);
			const float RandomNumberY = RandomNumber::RandomFloat(0,1000);
			Worm->SetWorldPosition(sf::Vector2f(RandomNumberX, RandomNumberY));
			
			//Worm->SetWorldPosition(sf::Vector2f(rand() % 1000, rand() % 1000));
		}
	}

	//get random worm in random team
	CurrentTeamIndex = RandomNumber::RandomInt(0,NbTeams - 1);
	Team* thisTeam = Teams[CurrentTeamIndex].get();
	Character* thisWorms = SetCharacterControlled(thisTeam->Worms[RandomNumber::RandomInt(0,NbWormsInTeam - 1)].get());

	Worm* thisWorm = dynamic_cast<Worm*>(thisWorms);

	thisWorm->bIsControlled = true;
	thisWorm->bCanFire = true;
	thisWorm->bCanMove = true;	

	/*Worms.push_back(MainWorm);
	Worms.push_back(AnotherWorm);

	MainWorm->SetName("p1");*/

	/*MainWorm->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);
	AnotherWorm->DeleguateActionDone->AddCallback(this, &LevelRules::SwitchCharacter);*/

	/*AnotherWorm->SetName("p2");

	AddGameObject(MainWorm);
	AddGameObject(AnotherWorm);

	AnotherWorm->SetWorldPosition(sf::Vector2f(200, 200));*/

	/*SetCharacterControlled(MainWorm.get());
	MainWorm->bIsControlled = true;
	MainWorm->bCanFire = true;
	MainWorm->bCanMove = true;*/

	// Shapes
	std::shared_ptr<Square> Square1 = std::make_shared<Square>();
	Square1->SetWorldPosition(sf::Vector2f(400, 400));
	Square1->SquareColliderComponent->SetSize(sf::Vector2f(700, 200));
	Square1->SquareColliderComponent->SetMobility(EMobility::Stationary);
	AddGameObject(Square1);

	InitGrid();
}

void LevelRules::Start()
{
	Level::Start();
}

void LevelRules::Update(const float DeltaTime)
{
	Level::Update(DeltaTime);
}

void LevelRules::InitGrid()
{
	// Grid
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
		{
			std::shared_ptr<Square> Square1 = std::make_shared<Square>();
			Square1->SetWorldPosition(sf::Vector2f(100 * col, 100 * row));
			Square1->SquareColliderComponent->SetSize(sf::Vector2f(100, 100));
			Square1->SquareColliderComponent->SetMobility(EMobility::Stationary);
			AddGameObject(Square1);
		}

	}

}

void LevelRules::SwitchCharacter()
{
	////get next worm in the other team
	const Team* thisTeam = Teams[CurrentTeamIndex].get();

	const std::shared_ptr<Worm> actualWorm = thisTeam->LastWorm;
	actualWorm->bIsControlled = false;
	actualWorm->bCanFire = false;
	actualWorm->bCanMove = false;

	if(CurrentTeamIndex == Teams.size() - 1)
	{
		CurrentTeamIndex = 0;
	}
	else
	{
		CurrentTeamIndex++;
	}

	const std::shared_ptr<Worm> nextWorm = Teams[CurrentTeamIndex]->GetNextWorm();
	Character* thisWorms = SetCharacterControlled(nextWorm.get());

	Worm* thisWorm = dynamic_cast<Worm*>(thisWorms);

	thisWorm->bIsControlled = true;
	thisWorm->bCanFire = true;
	thisWorm->bCanMove = true;


	/*for (auto &Worm : Worms)
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
	}*/
}
