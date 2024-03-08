#pragma once

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp> // Inclusion nécessaire pour sf::Vector2f en raison de sa nature en tant que type de template spécialisé
#include <string>

class IComponent;
class Transform;
class Level;

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class GameObject
{
public:
    virtual ~GameObject() = default;

    GameObject();

    //
    virtual void Start();

    // Met à jour tous les composants du GameObject.
    virtual void Update(const float DeltaTime);

    // Appelle la méthode de rendu sur tous les composants du GameObject.
    virtual void Render(sf::RenderWindow &Window) const;

    // Ajoute un composant au GameObject.
    void AddComponent(IComponent *Component);
    // void AddComponent(std::shared_ptr<IComponent> Component);

    // Récupère un composant de type spécifique attaché au GameObject.
    template <typename T>
    T *GetComponent() const;
    // std::shared_ptr<T> GetComponent() const;

    template <typename T>
    void RemoveComponent();

    void RemoveComponent(IComponent *ComponentToRemove);

    // Incrémente position monde du GameObject.
    void AddWorldPosition(const sf::Vector2f &AmountPosition);

    // Incrémente position relative du GameObject.
    void AddRelativePosition(const sf::Vector2f &AmountPosition);

    // Définit la position monde du GameObject.
    void SetWorldPosition(const sf::Vector2f &Position);

    // Définit la position relative du GameObject.
    void SetRelativePosition(const sf::Vector2f &Position);

    // Définit l'échelle du GameObject.
    void SetWorldScale(const sf::Vector2f &Scale);

    // Définit l'échelle relative du GameObject.
    void SetRelativeScale(const sf::Vector2f &Scale);

    // Définit la rotation du GameObject.
    void SetWorldRotation(const float Rotation);

    // Définit la rotation relative du GameObject.
    void SetRelativeRotation(const float Rotation);

    // Récupère la position actuelle du GameObject.
    sf::Vector2f GetWorldPosition() const;

    // Récupère la position relative actuelle du GameObject.
    sf::Vector2f GetRelativePosition() const;

    // Récupère l'échelle actuelle du GameObject.
    sf::Vector2f GetWorldScale() const;

    // Récupère l'échelle relative actuelle du GameObject.
    sf::Vector2f GetRelativeScale() const;

    // Récupère la rotation actuelle du GameObject.
    float GetWorldRotation() const;

    // Récupère la rotation relative actuelle du GameObject.
    float GetRelativeRotation() const;

    // Récupère une référence partagée vers le composant Transform du GameObject.
    std::shared_ptr<Transform> GetWorldTransform() const;

    // Déinifit le nom du GameObject.
    void SetName(const std::string &NewName);

    // Récupère le nom du GameObject.
    std::string GetName() const;

    // Set le Level à qui appartient le GameObject
    void SetLevel(Level *Level);

    // Récupère le Level
    Level *GetWorld();

    // Détruit le GameObject du Level
    virtual void Destroy(GameObject *GameObjectToDestroy = nullptr);

protected:
private:
    Level *OwnerLevel; // Pointeur vers le levle propriétaire.

    std::string Name;

    // Liste des composants attachés à ce GameObject.
    std::vector<IComponent *> Components;
    // std::vector<std::shared_ptr<IComponent>> Components;

    // Composant Transform spécifique gérant la position, l'échelle et la rotation du GameObject.
    std::shared_ptr<Transform> WorldTransformComponent;

    // Composant Transform spécifique gérant la position, l'échelle et la rotation relative du GameObject.
    std::shared_ptr<Transform> RelativeTransformComponent;

    void UpdateComponentsPosition();
};

#include "GameObject.tpp"