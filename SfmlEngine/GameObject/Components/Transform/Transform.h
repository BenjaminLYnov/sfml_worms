#pragma once

#include "./../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML

// La classe Transform hérite de Component et gère la position, l'échelle et la rotation d'un GameObject.
class Transform : public IComponent
{
public:
    // Constructeur par défaut qui initialise les valeurs de position, échelle et rotation.
    Transform();

    // Déclaration des fonctions virtuelles héritées de Component.
    virtual void Start() override;
    virtual void Update(const float DeltaTime) override;

    // Définit la position du GameObject.
    void SetPosition(const sf::Vector2f &NewPosition);

    // Définit l'échelle du GameObject.
    void SetScale(const sf::Vector2f &NewScale);

    // Définit la rotation du GameObject (en degrés).
    void SetRotation(const float NewRotation);

    // Récupère la position actuelle du GameObject.
    const sf::Vector2f &GetPosition() const;

    // Récupère l'échelle actuelle du GameObject.
    const sf::Vector2f &GetScale() const;

    // Récupère la rotation actuelle du GameObject (en degrés).
    float GetRotation() const;

private:
    sf::Vector2f Position; // Stocke la position 2D du GameObject.
    sf::Vector2f Scale;    // Stocke l'échelle 2D du GameObject.
    float Rotation;        // Stocke la rotation du GameObject en degrés.
};
