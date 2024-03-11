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
    UIImage* portrait;
    UIText* name;
    UIText* health;

    PlayerInfos()
    {
        portrait = nullptr;
        name = nullptr;
        health = nullptr;
    }

    void SetPortrait(UIImage* _portrait){portrait = _portrait;}
    void SetName(UIText* _name){name = _name;}
    void SetHealth(UIText* _health){health = _health;}

    void UpdateHealth(int _health)
    {
        if(health != nullptr) health->SetText(std::to_string(_health));
    }

    void UpdateName(const std::string& _name)
    {
        if(name != nullptr) name->SetText(_name);
    }
};



class UIConstructor
{
public:

    UIConstructor();

    std::shared_ptr<Canvas> CreateTopCanvas();
    std::shared_ptr<Canvas> CreateDownCanvas();

    PlayerInfos* GetPlayer1Infos(){return structPlayer1Infos;}
    PlayerInfos* GetPlayer2Infos(){return structPlayer2Infos;}

private:
    sf::Font font;

    PlayerInfos* structPlayer1Infos;
    PlayerInfos* structPlayer2Infos;
    
};
