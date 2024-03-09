#pragma once
#include <memory>

#include "SFML/Graphics/Font.hpp"

class Deleguate;

class UIImage;
class UIText;
class Canvas;

struct PlayerInfos
{
    UIImage* portrait;
    UIText* name;
    UIText* health;
};



class UIConstructor
{
public:

    UIConstructor();

    std::shared_ptr<Canvas> CreateTopCanvas();
    std::shared_ptr<Canvas> CreateDownCanvas();

    PlayerInfos player1Infos;
    PlayerInfos player2Infos;

private:
    sf::Font font;
    
};
