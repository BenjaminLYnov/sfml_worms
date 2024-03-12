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
    // Méthode virtuelle pure pour l'initialisation du composant.
    virtual void Start() = 0;

    // Méthode virtuelle pure pour la mise à jour du composant.
    virtual void Update(const float DeltaTime) = 0;

    virtual void UpdatePosition();

    // Effectue le rendu du component
    virtual void Render(sf::RenderWindow &Window);

    // Attribue le GameObject propriétaire de ce composant.
    void SetOwner(GameObject* Owner);

    // Récupère le GameObject propriétaire de ce composant.
    GameObject* GetOwner();

protected:
    

private:
    GameObject* Owner = nullptr; // Pointeur vers le GameObject propriétaire.
};
