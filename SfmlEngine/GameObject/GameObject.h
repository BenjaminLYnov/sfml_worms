#pragma once

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour sf::Vector2f en raison de sa nature en tant que type de template spécialisé

class IComponent;
class Transform;

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class GameObject
{
public:
    GameObject();

    // 
    virtual void Start() = 0;

    // Met à jour tous les composants du GameObject.
    virtual void Update(const float DeltaTime) = 0;

    // Appelle la méthode de rendu sur tous les composants du GameObject.
    virtual void Render(sf::RenderWindow &Window) const = 0;

    // Ajoute un composant au GameObject.
    void AddComponent(std::shared_ptr<IComponent> Component);

    // Récupère un composant de type spécifique attaché au GameObject.
    template <typename T>
    std::shared_ptr<T> GetComponent() const;

    // Définit la position du GameObject.
    void SetPosition(const sf::Vector2f &Position);

    // Définit l'échelle du GameObject.
    void SetScale(const sf::Vector2f &Scale);

    // Définit la rotation du GameObject.
    void SetRotation(float Rotation);

    // Récupère la position actuelle du GameObject.
    sf::Vector2f GetPosition() const;

    // Récupère l'échelle actuelle du GameObject.
    sf::Vector2f GetScale() const;

    // Récupère la rotation actuelle du GameObject.
    float GetRotation() const;

    // Récupère une référence partagée vers le composant Transform du GameObject.
    std::shared_ptr<Transform> GetTransform() const;

private:
    // Liste des composants attachés à ce GameObject.
    std::vector<std::shared_ptr<IComponent>> Components;

    // Composant Transform spécifique gérant la position, l'échelle et la rotation du GameObject.
    std::shared_ptr<Transform> TransformComponent;
};