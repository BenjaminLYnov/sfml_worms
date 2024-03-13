#pragma once
#include <memory>

#include "SFML/Graphics/Font.hpp"
#include "UI/UIImage.h"
#include "UI/UIText.h"

class Deleguate;

class UIImage;
class UIText;
class Canvas;

struct PlayerInfos
{
    
    std::shared_ptr<UIImage> portrait;
    std::shared_ptr<UIText> name;
    std::shared_ptr<UIText> health;
    std::shared_ptr<UIImage> heart;

    bool isGreyed;

    PlayerInfos()
    {
        portrait = nullptr;
        name = nullptr;
        health = nullptr;
        heart = nullptr;
        isGreyed = false;
    }

    void SetPortrait(std::shared_ptr<UIImage>& _portrait){portrait = _portrait;}
    void SetName(std::shared_ptr<UIText>& _name){name = _name;}
    void SetHealth(std::shared_ptr<UIText>& _health){health = _health;}
    void SetHealth(int _health){health->SetText(std::to_string(_health));}

    void UpdateHealth(int _health)
    {
        if(health != nullptr) health->SetText(std::to_string(_health));
    }

    void UpdateName(const std::string& _name)
    {
        if(name != nullptr) name->SetText(_name);
    }

    void GreyPlayer(bool _greyed)
    {
        if(portrait != nullptr) portrait->SetGreyed(_greyed);
        if(name != nullptr) name->SetGreyed(_greyed);
        if(health != nullptr) health->SetGreyed(_greyed);
        if(heart != nullptr) heart->SetGreyed(_greyed);
        isGreyed = _greyed;
    }

    void SwitchGreyState()
    {
        GreyPlayer(!isGreyed);
    }
};



class UIConstructor
{
public:

    UIConstructor();

    std::shared_ptr<Canvas> CreateTopCanvas();
    std::shared_ptr<Canvas> CreateDownCanvas();
    std::shared_ptr<Canvas> CreateEditorCanvas();

    std::shared_ptr<PlayerInfos> GetPlayer1Infos(){return structPlayer1Infos;}
    std::shared_ptr<PlayerInfos> GetPlayer2Infos(){return structPlayer2Infos;}

    void SwitchWindDirection(bool _left);
    void SetWindForce(int _force);

    void SetActualPlayer(std::shared_ptr<PlayerInfos>& player){actualPlayer = player;}
    void SwitchPlayer();
    
    std::shared_ptr<UIImage> pistol;
    std::shared_ptr<UIImage> grenade;
    std::shared_ptr<UIImage> gravit;

    std::shared_ptr<PlayerInfos> actualPlayer;

private:

    bool windIsLeft = false;
    sf::Font font;

    std::shared_ptr<PlayerInfos> structPlayer1Infos;
    std::shared_ptr<PlayerInfos> structPlayer2Infos;
    
    std::shared_ptr<UIImage> windDirection;
    std::shared_ptr<UIText> windForceText;
};
