﻿#include "UIConstructor.h"

#include "Deleguate.h"
#include "UI/Canvas.h"
#include "UI/UIImage.h"
#include "UI/UIPanel.h"
#include "UI/UIText.h"

UIConstructor::UIConstructor()
{
	font = sf::Font();
	font.loadFromFile("arial.ttf");
	structPlayer1Infos = std::make_shared<PlayerInfos>();
	structPlayer2Infos = std::make_shared<PlayerInfos>();
}

std::shared_ptr<Canvas> UIConstructor::CreateTopCanvas()
{
    std::shared_ptr<Canvas> TopHUD = std::make_shared<Canvas>(Vec2f(0, 0), Vec2f(1165, 200));

	std::shared_ptr<UIPanel> HorizontalTopHUDPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(1, 1));
	
	HorizontalTopHUDPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	HorizontalTopHUDPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Start);
	
	std::shared_ptr<UIPanel> Player1HUD = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.3f, 0.6f));
	Player1HUD->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1HUD->SetAlignment(UIAlignment::Start, UIAlignment::Start);

	std::shared_ptr<UIPanel> Player1AvatarPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.8f, 0.75f));
	Player1AvatarPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1AvatarPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	std::shared_ptr<UIImage> Player1Avatar = std::make_shared<UIImage>("Sprites/spoune.jpg", Vec2f(0, 0), Vec2f(0.4f, 1));
	structPlayer1Infos->SetPortrait(Player1Avatar);
	Player1AvatarPanel->AddChild(Player1Avatar);
	
	std::shared_ptr<UIPanel> Player1Infos = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.5f, 0.8f));
	Player1Infos->SetLayout(UILayout::List, UIDirection::Vertical);
	Player1Infos->SetAlignment(UIAlignment::Center, UIAlignment::Center);
	Player1AvatarPanel->AddChild(Player1Infos);
	
	std::shared_ptr<UIText> Player1Name = std::make_shared<UIText>("Joachim", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f,0.4f), 20);
	structPlayer1Infos->SetName(Player1Name);
	Player1Infos->AddChild(Player1Name);

	std::shared_ptr<UIPanel> Player1LifePanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(1.f, 0.5f));
	Player1LifePanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1LifePanel->SetAlignment(UIAlignment::Start, UIAlignment::End);

	std::shared_ptr<UIText> Player1Life = std::make_shared<UIText>("100", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.5f), 20);
	structPlayer1Infos->SetHealth(Player1Life);
	Player1LifePanel->AddChild(Player1Life);

	std::shared_ptr<UIImage> Player1Heart = std::make_shared<UIImage>("Sprites/heart.png", Vec2f(0, 0), Vec2f(0.2f, 0.6f), sf::Color::Red);
	Player1LifePanel->AddChild(Player1Heart);

	Player1Infos->AddChild(Player1LifePanel);
	
	Player1HUD->AddChild(Player1AvatarPanel);

	
	std::shared_ptr<UIPanel> Player2HUD = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.3f, 0.6f));
	Player2HUD->SetLayout(UILayout::List, UIDirection::Vertical);
	Player2HUD->SetAlignment(UIAlignment::End, UIAlignment::SpaceBetween);

	std::shared_ptr<UIPanel> Player2AvatarPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.8f, 0.75f));
	Player2AvatarPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player2AvatarPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	std::shared_ptr<UIPanel> Player2Infos = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.5f, 0.8f));
	Player2Infos->SetLayout(UILayout::List, UIDirection::Vertical);
	Player2Infos->SetAlignment(UIAlignment::Center, UIAlignment::Center);
	Player2AvatarPanel->AddChild(Player2Infos);

	std::shared_ptr<UIImage> Player2Avatar = std::make_shared<UIImage>("Sprites/spoune.jpg", Vec2f(0, 0), Vec2f(0.4f, 1));
	structPlayer2Infos->SetPortrait(Player2Avatar);
	Player2AvatarPanel->AddChild(Player2Avatar);

	std::shared_ptr<UIText> Player2Name = std::make_shared<UIText>("Frederic", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.4f), 20);
	structPlayer2Infos->SetName(Player2Name);
	Player2Infos->AddChild(Player2Name);

	std::shared_ptr<UIPanel> Player2LifePanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(1.f, 0.5f));
	Player2LifePanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player2LifePanel->SetAlignment(UIAlignment::Start, UIAlignment::End);

	std::shared_ptr<UIText> PlayerLife = std::make_shared<UIText>("100", font, Vec2f(0.1f, 0.1f), Vec2f(0.6f, 0.5f), 20);
	structPlayer2Infos->SetHealth(PlayerLife);
	Player2LifePanel->AddChild(PlayerLife);

	std::shared_ptr<UIImage> Player2Heart = std::make_shared<UIImage>("Sprites/heart.png", Vec2f(0, 0), Vec2f(0.2f, 0.6f), sf::Color::Red);
	Player2LifePanel->AddChild(Player2Heart);

	Player2Infos->AddChild(Player2LifePanel);
	Player2HUD->AddChild(Player2AvatarPanel);
	
	std::shared_ptr<UIPanel> WindPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.2f, 0.7f));
	WindPanel->SetLayout(UILayout::List, UIDirection::Vertical);
	WindPanel->SetAlignment(UIAlignment::Center, UIAlignment::SpaceAround);

	std::shared_ptr<UIImage> WindLogo = std::make_shared<UIImage>("Sprites/wind.png", Vec2f(0, 0), Vec2f(0.2f, 0.3f));
	WindPanel->AddChild(WindLogo);
	
	std::shared_ptr<UIPanel> WindArrowPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.9f, 0.5f));
	WindArrowPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	WindArrowPanel->SetAlignment(UIAlignment::Center, UIAlignment::Start);

	std::shared_ptr<UIText> WindForce = std::make_shared<UIText>("3 m/s", font, Vec2f(0.1f, 0.1f), Vec2f(0.4f, 0.4f), 15);
	WindForce->SetColor(sf::Color::White, sf::Color::White);
	WindArrowPanel->AddChild(WindForce);
	
	std::shared_ptr<UIImage> WindArrow = std::make_shared<UIImage>("Sprites/arrow.png", Vec2f(0, 0), Vec2f(0.15f, 0.4f));
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
	std::shared_ptr<Canvas> BottomHUD = std::make_shared<Canvas>(Vec2f(0, 800), Vec2f(780, 100));

	std::shared_ptr<UIPanel> HorizontalBottomHUDPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(1, 1));
	HorizontalBottomHUDPanel->SetLayout(UILayout::List, UIDirection::Horizontal);
	HorizontalBottomHUDPanel->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);

	std::shared_ptr<UIPanel> Player1WeaponPanel = std::make_shared<UIPanel>(Vec2f(0, 0), Vec2f(0.25f, 1.f));
	Player1WeaponPanel->SetLayout(UILayout::List, UIDirection::Vertical);
	Player1WeaponPanel->SetAlignment(UIAlignment::Center, UIAlignment::SpaceBetween);

	std::shared_ptr<UIPanel> Player1WeaponIcons = std::make_shared<UIPanel>(Vec2f(0,0), Vec2f(0.8f, 0.6f));
	Player1WeaponIcons->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1WeaponIcons->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::End);
	Player1WeaponPanel->AddChild(Player1WeaponIcons);

	std::shared_ptr<UIImage> Gun1 = std::make_shared<UIImage>("Sprites/pistol.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));
	std::shared_ptr<UIImage> Grenade1 = std::make_shared<UIImage>("Sprites/grenade.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));
	std::shared_ptr<UIImage> Gravit1 = std::make_shared<UIImage>("Sprites/gravit.png", Vec2f(0, 0), Vec2f(0.3f, 0.8f));

	Player1WeaponIcons->AddChild(Gun1);
	Player1WeaponIcons->AddChild(Grenade1);
	Player1WeaponIcons->AddChild(Gravit1);

	std::shared_ptr<UIPanel> Player1WeaponsMunitions = std::make_shared<UIPanel>(Vec2f(0,0), Vec2f(0.8f, 0.2f));
	Player1WeaponsMunitions->SetLayout(UILayout::List, UIDirection::Horizontal);
	Player1WeaponsMunitions->SetAlignment(UIAlignment::SpaceBetween, UIAlignment::Center);
	Player1WeaponPanel->AddChild(Player1WeaponsMunitions);

	std::shared_ptr<UIImage> Infinity = std::make_shared<UIImage>("Sprites/infinity.png", Vec2f(0,0), Vec2f(0.2f, 0.7f));
	std::shared_ptr<UIText> Explode = std::make_shared<UIText>("3/3", font, Vec2f(0,0), Vec2f(0.15f, 0.3f), 20);
	std::shared_ptr<UIText> GravitMun = std::make_shared<UIText>("1/1", font, Vec2f(0,0), Vec2f(0.15f, 0.3f), 20);
	
	Player1WeaponsMunitions->AddChild(Infinity);
	Player1WeaponsMunitions->AddChild(Explode);
	Player1WeaponsMunitions->AddChild(GravitMun);
	
	HorizontalBottomHUDPanel->AddChild(Player1WeaponPanel);

	BottomHUD->AddChild(HorizontalBottomHUDPanel);

	BottomHUD->InitResources();
	return BottomHUD;
}