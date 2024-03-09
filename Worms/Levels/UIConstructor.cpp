#include "UIConstructor.h"

#include "Deleguate.h"
#include "UI/Canvas.h"
#include "UI/UIImage.h"
#include "UI/UIPanel.h"
#include "UI/UIText.h"

UIConstructor::UIConstructor()
{
	font = sf::Font();
	font.loadFromFile("arial.ttf");
	structPlayer1Infos = new PlayerInfos();
	structPlayer2Infos = new PlayerInfos();
}

std::shared_ptr<Canvas> UIConstructor::CreateTopCanvas()
{
    std::shared_ptr<Canvas> TopHUD = std::make_shared<Canvas>(Vec2f(10, 10), Vec2f(780, 130));
	
	UIPanel* HorizontalTopHUDPanel = new UIPanel(Vec2f(0, 0), Vec2f(1, 1));
	
	HorizontalTopHUDPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	HorizontalTopHUDPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Start);
	
	UIPanel* Player1HUD = new UIPanel(Vec2f(0, 0), Vec2f(0.3f, 0.6f));
	Player1HUD->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1HUD->SetAlignment(UIAlignment::Start, UIAlignment::Start);

	UIPanel* Player1AvatarPanel = new UIPanel(Vec2f(0, 0), Vec2f(0.8f, 0.75f));
	Player1AvatarPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1AvatarPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	UIImage* Player1Avatar = new UIImage("Sprites/spoune.jpg", Vec2f(0, 0), Vec2f(0.4f, 1));
	structPlayer1Infos->SetPortrait(Player1Avatar);
	Player1AvatarPanel->AddChild(Player1Avatar);
	
	UIPanel* Player1Infos = new UIPanel(Vec2f(0, 0), Vec2f(0.5f, 0.8f));
	Player1Infos->SetLayout(UILayout::List, UIDirection::Vertical);
	Player1Infos->SetAlignment(UIAlignment::Center, UIAlignment::Center);
	Player1AvatarPanel->AddChild(Player1Infos);
	
	UIText* Player1Name = new UIText("Joachim", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f,0.4f), 20);
	structPlayer1Infos->SetName(Player1Name);
	Player1Infos->AddChild(Player1Name);

	UIPanel* Player1LifePanel = new UIPanel(Vec2f(0, 0), Vec2f(1.f, 0.5f));
	Player1LifePanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1LifePanel->SetAlignment(UIAlignment::Start, UIAlignment::End);

	UIText* Player1Life = new UIText("100", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.5f), 20);
	structPlayer1Infos->SetHealth(Player1Life);
	Player1LifePanel->AddChild(Player1Life);

	UIImage* Player1Heart = new UIImage("Sprites/heart.png", Vec2f(0, 0), Vec2f(0.2f, 0.6f), sf::Color::Red);
	Player1LifePanel->AddChild(Player1Heart);

	Player1Infos->AddChild(Player1LifePanel);
	
	Player1HUD->AddChild(Player1AvatarPanel);

	
	UIPanel* Player2HUD = new UIPanel(Vec2f(0, 0), Vec2f(0.3f, 0.6f));
	Player2HUD->SetLayout(UILayout::List, UIDirection::Vertical);
	Player2HUD->SetAlignment(UIAlignment::End, UIAlignment::SpaceBetween);

	UIPanel* Player2AvatarPanel = new UIPanel(Vec2f(0, 0), Vec2f(0.8f, 0.75f));
	Player2AvatarPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player2AvatarPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	UIPanel* Player2Infos = new UIPanel(Vec2f(0, 0), Vec2f(0.5f, 0.8f));
	Player2Infos->SetLayout(UILayout::List, UIDirection::Vertical);
	Player2Infos->SetAlignment(UIAlignment::Center, UIAlignment::Center);
	Player2AvatarPanel->AddChild(Player2Infos);

	UIImage* Player2Avatar = new UIImage("Sprites/spoune.jpg", Vec2f(0, 0), Vec2f(0.4f, 1));
	structPlayer2Infos->SetPortrait(Player2Avatar);
	Player2AvatarPanel->AddChild(Player2Avatar);

	UIText* Player2Name = new UIText("Frederic", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.4f), 20);
	structPlayer2Infos->SetName(Player2Name);
	Player2Infos->AddChild(Player2Name);

	UIPanel* Player2LifePanel = new UIPanel(Vec2f(0, 0), Vec2f(1.f, 0.5f));
	Player2LifePanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player2LifePanel->SetAlignment(UIAlignment::Start, UIAlignment::End);

	UIText* PlayerLife = new UIText("100", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.5f), 20);
	structPlayer2Infos->SetHealth(PlayerLife);
	Player2LifePanel->AddChild(PlayerLife);

	UIImage* Player2Heart = new UIImage("Sprites/heart.png", Vec2f(0, 0), Vec2f(0.2f, 0.6f), sf::Color::Red);
	Player2LifePanel->AddChild(Player2Heart);

	Player2Infos->AddChild(Player2LifePanel);
	Player2HUD->AddChild(Player2AvatarPanel);
	
	UIPanel* WindPanel = new UIPanel(Vec2f(0, 0), Vec2f(0.2f, 0.7f));
	WindPanel->SetLayout(UILayout::List, UIDirection::Vertical);
	WindPanel->SetAlignment(UIAlignment::Center, UIAlignment::SpaceAround);

	UIImage* WindLogo = new UIImage("Sprites/wind.png", Vec2f(0, 0), Vec2f(0.2f, 0.3f));
	WindPanel->AddChild(WindLogo);
	
	UIPanel* WindArrowPanel = new UIPanel(Vec2f(0, 0), Vec2f(0.9f, 0.5f));
	WindArrowPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	WindArrowPanel->SetAlignment(UIAlignment::Center, UIAlignment::Start);

	UIText* WindForce = new UIText("3 m/s", font, Vec2f(0.1f, 0.1f), Vec2f(0.4f, 0.4f), 15);
	WindForce->SetColor(sf::Color::White, sf::Color::White);
	WindArrowPanel->AddChild(WindForce);
	
	UIImage* WindArrow = new UIImage("Sprites/arrow.png", Vec2f(0, 0), Vec2f(0.15f, 0.4f));
	WindArrowPanel->AddChild(WindArrow);
	
	WindPanel->AddChild(WindArrowPanel);
	

	HorizontalTopHUDPanel->AddChild(Player1HUD);
	HorizontalTopHUDPanel->AddChild(WindPanel);
	HorizontalTopHUDPanel->AddChild(Player2HUD);
	
	TopHUD->AddChild(HorizontalTopHUDPanel);
	TopHUD->InitResources();
	return TopHUD;
}

std::shared_ptr<Canvas> UIConstructor::CreateDownCanvas()
{
	std::shared_ptr<Canvas> BottomHUD = std::make_shared<Canvas>(Vec2f(10, 480), Vec2f(780, 100));

	UIPanel* HorizontalBottomHUDPanel = new UIPanel(Vec2f(0, 0), Vec2f(1, 1));
	HorizontalBottomHUDPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	HorizontalBottomHUDPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	UIPanel* Player1WeaponPanel = new UIPanel(Vec2f(0, 0), Vec2f(0.25f, 1.f));
	Player1WeaponPanel->SetLayout(UILayout::List, UIDirection::Vertical);
	Player1WeaponPanel->SetAlignment(UIAlignment::Center, UIAlignment::SpaceBetween);

	UIPanel* Player1WeaponIcons = new UIPanel(Vec2f(0,0), Vec2f(0.8f, 0.6f));
	Player1WeaponIcons->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1WeaponIcons->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::End);
	Player1WeaponPanel->AddChild(Player1WeaponIcons);

	UIImage* Gun1 = new UIImage("Sprites/pistol.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));
	UIImage* Grenade1 = new UIImage("Sprites/grenade.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));
	UIImage* Gravit1 = new UIImage("Sprites/gravit.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));

	Player1WeaponIcons->AddChild(Gun1);
	Player1WeaponIcons->AddChild(Grenade1);
	Player1WeaponIcons->AddChild(Gravit1);

	UIPanel* Player1WeaponsMunitions = new UIPanel(Vec2f(0,0), Vec2f(0.8f, 0.2f));
	Player1WeaponsMunitions->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1WeaponsMunitions->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);
	Player1WeaponPanel->AddChild(Player1WeaponsMunitions);

	UIImage* Infinity = new UIImage("Sprites/infinity.png", Vec2f(0,0), Vec2f(0.2f, 0.7f));
	UIText* Explode = new UIText("3/3", font, Vec2f(0,0), Vec2f(0.15f, 0.3f), 20);
	UIText* GravitMun = new UIText("1/1", font, Vec2f(0,0), Vec2f(0.15f, 0.3f), 20);
	
	Player1WeaponsMunitions->AddChild(Infinity);
	Player1WeaponsMunitions->AddChild(Explode);
	Player1WeaponsMunitions->AddChild(GravitMun);
	
	HorizontalBottomHUDPanel->AddChild(Player1WeaponPanel);

	BottomHUD->AddChild(HorizontalBottomHUDPanel);

	BottomHUD->InitResources();
	return BottomHUD;
}