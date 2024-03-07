#include "LevelRules.h"

#include "Deleguate.h"
#include "Characters/Worm/Worm.h"

#include "GameObject/Shapes/Square.h"
#include "GameObject/Shapes/Circle.h"
#include "GameObject/Components/Collider/SquareCollider.h"
#include "UI/Canvas.h"
#include "UI/UIImage.h"
#include "UI/UIPanel.h"
#include "UI/UIText.h"

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


	//Add a canvas
	std::shared_ptr<Canvas> TopHUD = std::make_shared<Canvas>(Vec2f(20, 20), Vec2f(200, 200));
	sf::Vector2<float> TopHudCanvasSize = TopHUD->GetSize();
	
	UIPanel* panel = new UIPanel(Vec2f(0.25f, 0.f), Vec2f((TopHudCanvasSize.x / 2) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 2) / TopHudCanvasSize.y));
	UIPanel* secondPanel = new UIPanel(Vec2f(0.25f, 0.75f), Vec2f((TopHudCanvasSize.x / 2) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 2) / TopHudCanvasSize.y));
	TopHUD->AddChild(panel);
	TopHUD->AddChild(secondPanel);

	UIPanel* leftPanel = new UIPanel(Vec2f(500, 0.25f), Vec2f((TopHudCanvasSize.x / 4) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 4) / TopHudCanvasSize.y));
	UIPanel* middlePanel = new UIPanel(Vec2f(0.25f, 0.25f), Vec2f((TopHudCanvasSize.x / 6) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 6) / TopHudCanvasSize.y));
	UIPanel* rightPanel = new UIPanel(Vec2f(0.25f, 0.25f), Vec2f((TopHudCanvasSize.x / 4) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 4) / TopHudCanvasSize.y));

	UIPanel* leftPanel2 = new UIPanel(Vec2f(500, 0.25f), Vec2f((TopHudCanvasSize.x / 4) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 4) / TopHudCanvasSize.y));
	UIPanel* middlePanel2 = new UIPanel(Vec2f(0.25f, 0.25f), Vec2f((TopHudCanvasSize.x / 6) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 6) / TopHudCanvasSize.y));
	UIPanel* rightPanel2 = new UIPanel(Vec2f(0.25f, 0.25f), Vec2f((TopHudCanvasSize.x / 4) / TopHudCanvasSize.x, (TopHudCanvasSize.y / 4) / TopHudCanvasSize.y));

	panel->AddChild(leftPanel);
	panel->AddChild(middlePanel);
	panel->AddChild(rightPanel);

	secondPanel->AddChild(leftPanel2);
	secondPanel->AddChild(middlePanel2);
	secondPanel->AddChild(rightPanel2);

	panel->SetLayout(UILayout::List, UIDirection::Horizontal);
	panel->SetHorizontalAlignment(UIAlignment::SpaceBetween);
	panel->SetVerticalAlignment(UIAlignment::Center);

	secondPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	secondPanel->SetHorizontalAlignment(UIAlignment::SpaceBetween);
	secondPanel->SetVerticalAlignment(UIAlignment::Center);

	
	std::string sTestImage = "spoune.jpg";
	sf::Font font;
	font.loadFromFile("arial.ttf");

	
	AddCanvas(TopHUD);
	TopHUD->InitResources();
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