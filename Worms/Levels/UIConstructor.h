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

    PlayerInfos()
    {
        portrait = nullptr;
        name = nullptr;
        health = nullptr;
    }

    void SetPortrait(std::shared_ptr<UIImage>& _portrait){portrait = _portrait;}
    void SetName(std::shared_ptr<UIText>& _name){name = _name;}
    void SetHealth(std::shared_ptr<UIText>& _health){health = _health;}

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

    std::shared_ptr<PlayerInfos> GetPlayer1Infos(){return structPlayer1Infos;}
    std::shared_ptr<PlayerInfos> GetPlayer2Infos(){return structPlayer2Infos;}

private:
    sf::Font font;

    std::shared_ptr<PlayerInfos> structPlayer1Infos;
    std::shared_ptr<PlayerInfos> structPlayer2Infos;
    
};
