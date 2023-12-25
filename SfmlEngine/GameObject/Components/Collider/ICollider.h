#pragma once

#include "../IComponent.h"
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour utiliser sf::Vector2f, un type de template spécialisé de la SFML

class Transform;

class ICollider : public IComponent
{
public:
    // Constructeur par défaut
    ICollider();

    virtual ~ICollider(); // Déclaration du destructeur

    // Redéfinition des méthodes virtuelles pures de IComponent.
    virtual void Start() override = 0;
    virtual void Update(const float DeltaTime) override = 0;
    virtual void Render(sf::RenderWindow &Window) override = 0;

    // Méthodes spécifiques à ICollider.
    virtual void OnCollisionEnter(ICollider *Other) = 0; // Appelé lors du début d'une collision
    virtual void OnCollisionStay(ICollider *Other) = 0;  // Appelé tant que la collision persiste
    virtual void OnCollisionExit(ICollider *Other) = 0;  // Appelé lorsqu'une collision prend fin

    void SetOffset(const sf::Vector2f &NewOffset);
    // void SetRelativeRotation(float rotation);

    sf::Vector2f GetOffset() const;
    // sf::Vector2f GetRelativeScale() const;
    // float GetRelativeRotation() const;

protected:
    sf::Vector2f Offset;
    // Composant Transform spécifique gérant la Offset, l'échelle et la rotation relative du collider.
    // Transform *RelativeTransformComponent;
    // std::shared_ptr<Transform> RelativeTransformComponent;
};
