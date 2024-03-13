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
#include "GameObject/Components/Ui/Text.h"
#include "Resources/Resources.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject/Components/Sound/Sound.h"
#include "Levels/UIConstructor.h"

Party::Party() : Level()
{
	SoundMatchNull = std::make_shared<Sound>(wbrb_data, wbrb_size);
	SoundWin = std::make_shared<Sound>(niveau_termine_data, niveau_termine_size);
}

void Party::Start()
{
	GameObjects.clear();
	CurrentWorm.reset();
	CurrentTeam.reset();

	if (SoundWin)
		SoundWin->Stop();

	if (SoundMatchNull)
		SoundMatchNull->Stop();

	TextEndParty = std::make_shared<Text>(arial_data, arial_size);
	TextEndParty->SetCharacterSize(50);
	TextEndParty->SetFillColor(sf::Color::Red);

	G = std::make_shared<Graph>();
	G->World = this;
	G->Init();
	G->EnableCellsCollision(true);

	DZ = std::make_shared<DeadZone>();
	DZ->SetWorldPosition(sf::Vector2f(0, 1500));
	AddGameObject(DZ);

	InitTeams();
	SetupUI();

	Level::Start();

	std::vector<std::shared_ptr<Worm>> Worms = GetAllGameObjectByClass<Worm>();
	for (int i = 0; i < Worms.size(); i++)
	{
		if (!Worms[i])
			continue;
		SpawnWorm(Worms[i]);
	}

	UpdateWindForce();
}

void Party::Update(const float DeltaTime)
{
	ApplyWindForceToRigidbody();

	Level::Update(DeltaTime);

	if (CurrentWorm)
	{
		if (CurrentWorm->CameraComponent)
		{
			TextEndParty->SetWorldPosition(CurrentWorm->CameraComponent->CurrentViewCenter);
		}
	}
}

void Party::Render(sf::RenderWindow &Window) const
{
	Level::Render(Window);
	TextEndParty->Render(Window);
}

void Party::SetupUI()
{
	UI = std::make_shared<UIConstructor>();

	AddCanvas(UI->CreateTopCanvas());
	AddCanvas(UI->CreateDownCanvas());

	Player1Infos = UI->GetPlayer1Infos();
	Player2Infos = UI->GetPlayer2Infos();
	UI->SetActualPlayer(Player1Infos);
	Player2Infos->GreyPlayer(true);

	UI->grenade->SetGreyed(true);
	UI->gravit->SetGreyed(true);
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
			W->DeleguateDeath->AddCallback(this, &Party::GameIsOver);
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
	if (!WormToSpawn)
		return;

	HitResult Hit;
	const int MaxIteration = 10000;
	int CurrentIteration = 0;

	const float MinPositionX = G->Cells[0]->GetWorldPosition().x + 100;
	const float MaxPositionX = G->Cells[G->Cells.size() - 1]->GetWorldPosition().x - 100;
	const float MinPositionY = G->Cells[0]->GetWorldPosition().y - 200;
	const float MaxPositionY = G->Cells[G->Cells.size() - 1]->GetWorldPosition().y - 300;

	do
	{
		const int PosX = RandomNumber::RandomInt(MinPositionX, MaxPositionX);
		const int PosY = RandomNumber::RandomInt(MinPositionY, MaxPositionY);
		const sf::Vector2f Position = sf::Vector2f(PosX, PosY);
		WormToSpawn->SetWorldPosition(Position);

		std::shared_ptr<ICollider> Collider = std::dynamic_pointer_cast<ICollider>(WormToSpawn->SquareColliderComponent);

		if (!Collider)
			return;

		for (std::shared_ptr<GameObject> Go : GameObjects)
		{
			if (!Go)
				continue;

			if (Go != WormToSpawn)
				continue;

			ICollider *ColliderToCheck = Go->GetComponent<ICollider>();

			if (!ColliderToCheck)
				continue;

			if (!ColliderToCheck->bEnableCollision)
				continue;

			Hit = Collider->TestCollision(ColliderToCheck);

			if (Hit.bIsOnCollision)
				return;
		}
		CurrentIteration++;

	} while (Hit.bIsOnCollision && CurrentIteration <= MaxIteration);

	WormToSpawn->SetWorldPosition(sf::Vector2f(RandomNumber::RandomInt(MinPositionX, MaxPositionX), MinPositionY));
}

void Party::SwitchCharacter()
{
	if (!CurrentTeam || !CurrentWorm)
		return;

	if (GameIsOver())
		return;

	CurrentTeam = GetNextTeam();
	CurrentTeam->UpdateToNextWorm();
	std::shared_ptr<Worm> CurrentWorm = CurrentTeam->GetCurrentWorm();
	UpdateCurrentWorm(CurrentWorm);
	UpdateWindForce();
	UI->SwitchPlayer();
	UI->actualPlayer->SetHealth(CurrentWorm->CurrentHealth);
	Player1Infos->SwitchGreyState();
	Player2Infos->SwitchGreyState();
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

std::shared_ptr<Team> Party::GetNextTeam()
{
	for (size_t i = 0; i < Teams.size(); i++)
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

bool Party::GameIsOver()
{
	if (Teams.size() == 0)
		return true;

	// Vérifier si tous les worms sont mort
	if (AllTeamAreDead())
	{
		std::string WinMessage = "Match null !";
		TextEndParty->SetString(WinMessage);
		if (SoundMatchNull)
			SoundMatchNull->Play();
		if (SoundWin)
			SoundWin->Stop();
		return true;
	}

	// Vérifier si une team n'a plus aucun worm
	for (int i = 0; i < Teams.size(); i++)
	{
		if (Teams[i]->GetWorms().size() == 0)
		{
			std::shared_ptr WinTeam = Teams[(i + 1) % Teams.size()];
			std::string WinMessage = WinTeam->GetName() + " a gagned la partie !";

			for (int i = 0; i < WinTeam->GetWorms().size(); i++)
			{
				if (WinTeam->GetWorms()[i])
				{
					WinTeam->GetWorms()[i]->SetWinAnimation();
				}
			}

			UpdateCurrentWorm(WinTeam->GetCurrentWorm());

			TextEndParty->SetString(WinMessage);
			if (SoundWin)
				SoundWin->Play();

			return true;
		}
	}
	return false;
}

void Party::ApplyWindForceToRigidbody()
{
	for (std::shared_ptr<GameObject> Go : GameObjects)
	{
		if (!Go)
			continue;

		Rigidbody *Rb = Go->GetComponent<Rigidbody>();

		if (!Rb)
			continue;

		if (Rb->GetVelocity().y == 0)
			continue;

		Rb->AddForce(WindForce * GetWorldDeltaSecond());
	}
}

void Party::UpdateWindForce()
{
	int XForce = RandomNumber::RandomInt(MinWindForce, MaxWindForce);

	if (RandomNumber::RandomInt(0, 1) == 1)
	{
		XForce *= -1;
	}

	WindForce = sf::Vector2f(XForce, 0);
	UI->SwitchWindDirection(XForce < 0);
	UI->SetWindForce(XForce / 1000);
}