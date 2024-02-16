#pragma once
#include "memory"

class GameObject; // Prédéclaration pour éviter les inclusions circulaires.

// Forward declaration de sf::RenderWindow
namespace sf
{
    class RenderWindow;
}

class IComponent
{
public:
    // Destructeur virtuel pour assurer une destruction appropriée des classes dérivées.
    // virtual ~IComponent() = default;
    virtual ~IComponent();

    // Méthode virtuelle pure pour l'initialisation du composant.
    virtual void Start() = 0;

    // Méthode virtuelle pure pour la mise à jour du composant.
    virtual void Update(const float DeltaTime) = 0;

    virtual void UpdatePosition();

    // Effectue le rendu du component
    virtual void Render(sf::RenderWindow &Window);

    // Active le composant, permettant son utilisation.
    virtual void Enable();

    // Désactive le composant, le rendant inactif.
    virtual void Disable();

    // Attribue le GameObject propriétaire de ce composant.
    void SetOwner(GameObject* Owner);
    // void SetOwner(std::shared_ptr<GameObject> Owner);

    // Récupère le GameObject propriétaire de ce composant.
    GameObject* GetOwner();
    // std::shared_ptr<GameObject> GetOwner();

protected:
    

private:
    GameObject* Owner; // Pointeur vers le GameObject propriétaire.
    // std::shared_ptr<GameObject> Owner; // Pointeur vers le GameObject propriétaire.
};
