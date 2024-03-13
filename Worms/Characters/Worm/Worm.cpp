#include "Worm.h"
#include <iostream>
#include <cmath>
#include "Math/Vector/Vector.h"

// Inclusion des Components
#include "GameObject/Components/Collider/SquareCollider.h"
#include "GameObject/Components/Collider/CircleCollider.h"
#include "GameObject/Components/Collider/TriangleCollider.h"

#include "GameObject/Components/Input/InputAction/InputAction.h"
#include "GameObject/Components/Input/InputAction/Key/Key.h"
#include "GameObject/Components/Sprite/Sprite.h"
#include "GameObject/Components/Rigidbody/Rigidbody.h"

#include "Resources/Resources.h"

// Inclure les Animations
#include "GameObject/Components/Sprite/AnimatedSprite.h"
#include "Animations/IdleAnimation.h"
#include "Animations/WalkAnimation.h"
#include "Animations/JumpAnimation.h"
#include "Animations/WinAnimation.h"
#include "Animations/AimAnimation.h"

// Include les Inputs Action
#include "GameObject/Components/Input/TriggerEvent.h"
#include "Characters/InputActions/MoveAction.h"
#include "Characters/InputActions/JumpAction.h"
#include "Characters/InputActions/FireAction.h"
#include "Characters/InputActions/AimAction.h"
#include "Characters/InputActions/ZoomViewportAction.h"
#include "Characters/InputActions/ResetViewCenter.h"
#include "Characters/InputActions/MoveViewportAction.h"
#include "Characters/InputActions/MoveViewportAction.h"
#include "Characters/InputActions/LoadGraphEditionAction.h"
#include "Characters/InputActions/RestartPartyAction.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

// Weapon
#include "Items/Weapons/Projectiles/CannonBall.h"
// #include "Items/Weapons/Projectiles/FragmentationBall.h"
#include "Items/Weapons/Projectiles/Explosion.h"

#include "GameObject/Components/Ui/Text.h"
#include "GameObject/Components/Camera/Camera.h"

#include "Deleguate.h"
#include "Team.h"

#include "Level/Level.h"
#include "GameManager/GameManager.h"
#include "GameObject/Components/Sound/Sound.h"
#include "GameObject/Components/Ui/ProgressBar.h"

Worm::Worm() : Character()
{
    MaxWalkSpeed = 200;

    MaxHealth = 30;
    CurrentHealth = MaxHealth;
    bIsAlive = true;
    bCanMove = false;
    bCanFire = false;
    bIsAiming = false;
    bWon = false;
    bCanJump = true;

    // Instance Animations
    InitAnimations();

    // Init Components
    SquareColliderComponent = std::make_shared<SquareCollider>();
    SquareColliderComponent->SetSize(sf::Vector2f(30, 30));
    SquareColliderComponent->AddCallback(ECollisionEvent::Enter, this, &Worm::OnCollisionEnter);

    RigidbodyComponent = std::make_shared<Rigidbody>();
    RigidbodyComponent->GravityScale = 15;

    TextName = std::make_shared<Text>(arial_data, arial_size);
    TextName->SetCharacterSize(10);
    TextName->SetFillColor(sf::Color::Red);
    TextName->Offset = sf::Vector2f(0, -100);

    TextHp = std::make_shared<Text>(arial_data, arial_size);
    TextHp->SetCharacterSize(10);
    TextHp->SetFillColor(sf::Color::Red);
    TextHp->Offset = sf::Vector2f(0, -50);
    TextHp->SetString(std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));

    AddComponent(TextName.get());
    AddComponent(TextHp.get());
    AddComponent(SquareColliderComponent.get());
    AddComponent(RigidbodyComponent.get());

    // Instance Inputs Acitons
    IaMove = std::make_shared<MoveAction>();
    IaJump = std::make_shared<JumpAction>();
    IaFire = std::make_shared<FireAction>();
    IaAim = std::make_shared<AimAction>();
    IaMoveViewport = std::make_shared<MoveViewportAction>();
    IaZoomViewport = std::make_shared<ZoomViewportAction>();
    IaResetViewport = std::make_shared<ResetViewCenter>();
    IaLoadGraphEdition = std::make_shared<LoadGraphEditionAction>();
    IaRestartParty = std::make_shared<RestartPartyAction>();

    DeleguateFire = std::make_shared<Deleguate>();
    DeleguateActionDone = std::make_shared<Deleguate>();
    DeleguateDeath = std::make_shared<Deleguate>();

    SoundJump = std::make_shared<Sound>(firered_000A_data, firered_000A_size);
    SoundShoot = std::make_shared<Sound>(firered_00AA_data, firered_00AA_size);

    PB = std::make_shared<ProgressBar>(50, 10, sf::Color::Red, sf::Color::White);
}

void Worm::Start()
{
    Character::Start();
    SetupBindAction();
}

void Worm::Update(const float DeltaTime)
{

    if (!bWon && !bIsIncreasingShootForce && !bIsAiming && RigidbodyComponent->GetVelocity().y == 0 && std::abs(RigidbodyComponent->GetVelocity().x) <= 1)
    {
        SwitchAnimation(IdleA);
    }

    TextName->SetString(GetName());

    if (bIsFacingRight)
        AnimationComponent->SetScale(sf::Vector2f(-1, 1));
    else
        AnimationComponent->SetScale(sf::Vector2f(1, 1));

    Character::Update(DeltaTime);

    PB->SetPosition(GetWorldPosition() + sf::Vector2f(0, -20));
}

void Worm::Render(sf::RenderWindow &Window) const
{
    Character::Render(Window);
    DrawAimLine(Window);

    if (bIsAiming)
        PB->Render(Window);
}

void Worm::Destroy(GameObject *GameObjectToDestroy)
{
    if (Team)
        Team->RemoveWorm(this);
   
    GameObject::Destroy();
    CallDeleguateActionDone();
    DeleguateDeath->Broadcast();
}

float Worm::TakeDamage(const float Damage)
{
    CurrentHealth -= Damage;

    if (ExplosionS)
        ExplosionS->SetOwner();

    if (CurrentHealth <= 0)
    {
        CurrentHealth = 0;
        bIsAlive = false;
        Destroy();
    }

    TextHp->SetString(std::to_string(CurrentHealth) + "/" + std::to_string(MaxHealth));

    return CurrentHealth;
}

void Worm::SetWinAnimation()
{
    SwitchAnimation(WinA);
    bWon = true;
}

// PROTECTED

void Worm::SetupBindAction()
{
    InputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &Worm::Move);
    InputComponent->BindAction(IaMove, ETriggerEvent::Started, this, &Worm::OnMoveStart);
    InputComponent->BindAction(IaMove, ETriggerEvent::Completed, this, &Worm::OnMoveCompleted);
    InputComponent->BindAction(IaJump, ETriggerEvent::Started, this, &Worm::Jump);
    InputComponent->BindAction(IaFire, ETriggerEvent::Triggered, this, &Worm::OnFireTriggered);
    InputComponent->BindAction(IaFire, ETriggerEvent::Completed, this, &Worm::OnFireCompleted);
    InputComponent->BindAction(IaAim, ETriggerEvent::Triggered, this, &Worm::Aim);
    InputComponent->BindAction(IaMoveViewport, ETriggerEvent::Triggered, this, &Worm::MoveViewport);
    InputComponent->BindAction(IaZoomViewport, ETriggerEvent::Triggered, this, &Worm::ZoomViewport);
    InputComponent->BindAction(IaResetViewport, ETriggerEvent::Triggered, this, &Worm::ResetViewport);
    InputComponent->BindAction(IaRestartParty, ETriggerEvent::Started, this, &Worm::RestartParty);
    InputComponent->BindAction(IaLoadGraphEdition, ETriggerEvent::Started, this, &Worm::LoadGraphEdition);
}

void Worm::OnCollisionEnter(GameObject *GameObjectHited)
{
    // SetWorldPosition(sf::Vector2f(300, 200));
    // std::cout << "rara\n";
}

void Worm::InitAnimations()
{
    IdleA = std::make_shared<IdleAnimation>();
    WalkA = std::make_shared<WalkAnimation>();
    WinA = std::make_shared<WinAnimation>();
    JumpA = std::make_shared<JumpAnimation>();
    AimA = std::make_shared<AimAnimation>();
    SwitchAnimation(IdleA);
}

void Worm::Move(const sf::Vector2f Value)
{
    if (bWon)
        return;

    MoveDirection = Value;
    if (MoveDirection.x > 0)
    {
        AimDirection.x *= (bIsFacingRight ? 1.0f : -1.0f);
        bIsFacingRight = true;
    }
    else if (MoveDirection.x < 0)
    {
        AimDirection.x *= (bIsFacingRight ? -1.0f : 1.0f);
        bIsFacingRight = false;
    }

    if (!bCanMove)
        return;

    if (RigidbodyComponent->GetVelocity().y != 0)
        return;

    if (bIsIncreasingShootForce)
        return;

    SwitchAnimation(WalkA);
    const sf::Vector2f Force = Value * 1000.f;
    RigidbodyComponent->AddForce(Force);
}

void Worm::OnMoveStart(const sf::Vector2f Value)
{
    bIsMoving = true;

    if (!bIsIncreasingShootForce)
        bIsAiming = false;

    movementTimer = 0;
}

void Worm::OnMoveCompleted()
{
    bIsMoving = false;
    bIsAiming = false;
}

void Worm::Aim(const sf::Vector2f Value)
{
    if (bWon)
        return;

    bIsAiming = true;

    AimAngle += 1.0f * Value.y;
    AimAngle = std::clamp(AimAngle, MIN_AIM_ANGLE, MAX_AIM_ANGLE);
    if (bIsFacingRight)
    {
        AimDirection = sf::Vector2f(cos(AimAngle * M_PI / 180), sin(AimAngle * M_PI / 180));
    }
    else
    {
        AimDirection = sf::Vector2f(-cos(AimAngle * M_PI / 180), sin(AimAngle * M_PI / 180));
    }

    if (!bWon)
    {
        SwitchAnimation(AimA);
        AnimationComponent->Animation->SetFrameAt(DegreeToFrame(AimAngle));
    }
}

void Worm::DrawAimLine(sf::RenderWindow &window) const
{
    if (!bIsAiming)
        return;
    // Create a line segment from worm position to aim direction
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = GetWorldPosition();
    line[1].position = GetWorldPosition() + AimDirection * 100.0f; // Change 100.0f to set the magnitude of the vector

    // Set color of the line
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    // Draw the line
    window.draw(line);
}

void Worm::OnFireTriggered()
{
    if (bWon)
        return;

    if (!bCanFire)
        return;

    if (RigidbodyComponent->GetVelocity().y != 0)
        return;

    bIsIncreasingShootForce = true;

    ShootForce += ShootForceSpeedIncrease * GetWorld()->GetWorldDeltaSecond() * (bIncreaseShootForce ? 1 : -1);
    ShootForce = std::clamp(ShootForce, ShootForceMin, ShootForceMax);

    if (ShootForce >= ShootForceMax)
        bIncreaseShootForce = false;
    else if (ShootForce <= ShootForceMin)
        bIncreaseShootForce = true;

    PB->SetProgress(ShootForce / ShootForceMax);
    SwitchAnimation(AimA);
}

void Worm::OnFireCompleted()
{
    if (bWon)
        return;

    if (!bCanFire)
        return;

    if (RigidbodyComponent->GetVelocity().y != 0)
        return;

    bIsIncreasingShootForce = false;
    Fire();
    ShootForceTimer = 0;
    ShootForce = 0;
}

void Worm::Fire()
{
    if (bWon)
        return;

    if (!bCanFire)
        return;

    if (RigidbodyComponent->GetVelocity().y != 0)
        return;

    if (SoundShoot)
        SoundShoot->Play();

    const sf::Vector2f Location = GetWorldPosition() + AimDirection * 50.f;
    // FragmentationBallS = GetWorld()->SpawnGameObject<FragmentationBall>(Location);
    // FragmentationBallS->SetOwner(this);
    // FragmentationBallS->AddForce(AimDirection * 20000.f);
    // FragmentationBallS->DeleguateOnDestroy->AddCallback(this, &Worm::CallDeleguateActionDone);
    // FragmentationBallS = GetWorld()->SpawnGameObject<FragmentationBall>(Location);
    // FragmentationBallS->SetOwner(this);
    // sf::Vector2f force = AimDirection * ShootForce;

    CannonBallS = GetWorld()->SpawnGameObject<CannonBall>(Location);
    CannonBallS->SetOwner(this);
    CannonBallS->AddForce(AimDirection * ShootForce);
    CannonBallS->DeleguateOnDestroy->AddCallback(this, &Worm::CallDeleguateActionDone);

    if (!bWon)
    {
        SwitchAnimation(AimA);
        AnimationComponent->Animation->SetFrameAt(DegreeToFrame(AimAngle));
    }

    bCanFire = false;
    bCanMove = false;
    bCanJump = false;
    bIsAiming = false;
}

void Worm::Jump()
{
    if (bWon)
        return;

    if (!bCanJump)
        return;

    if (bIsIncreasingShootForce)
        return;

    if (RigidbodyComponent->GetVelocity().y != 0)
        return;

    bIsAiming = false;

    if (SoundJump)
        SoundJump->Play();

    RigidbodyComponent->ResetVelocity();
    RigidbodyComponent->AddForce(sf::Vector2f(JumpForce.x * (bIsFacingRight ? 1.0f : -1.0f), JumpForce.y));
    RigidbodyComponent->Update(GetWorld()->GetWorldDeltaSecond());

    SwitchAnimation(JumpA);
    AnimationComponent->Animation->SetStopAtLastFrame(true);
    AnimationComponent->Animation->RestartAnimation();
}

void Worm::MoveViewport(const sf::Vector2f Value)
{
    CameraComponent->Offset += (Value * SpeedMoveView * GetWorld()->GetWorldDeltaSecond());
}

void Worm::ZoomViewport(const sf::Vector2f Value)
{
    CameraComponent->SetZoom(CameraComponent->GetZoom() + Value.x * SpeedZoom * GetWorld()->GetWorldDeltaSecond());
}

void Worm::ResetViewport()
{
    CameraComponent->ResetViewport();
}

void Worm::RestartParty()
{
    GetWorld()->GM->LoadLevel("Party");
}

void Worm::LoadGraphEdition()
{
    GetWorld()->GM->LoadLevel("GraphEdition");
}

void Worm::CallDeleguateActionDone()
{
    if (GetWorld()->GetCharacterControlled().get() == this)
        DeleguateActionDone->Broadcast();
}

float Worm::GetShootForce()
{
    float result = 0;
    // calculate the shoot force in percentage
    if (ShootForceTimer < ShootForceTimerMax)
    {
        result = ShootForceTimer / ShootForceTimerMax * 100.0f;
    }
    else
    {
        result = 100.0f;
    }
    return result;
}

int Worm::DegreeToFrame(float Degree) const
{
    // Limite les valeurs de Degree entre -85 et 85
    if (Degree < -MAX_AIM_ANGLE)
        Degree = -MAX_AIM_ANGLE;
    if (Degree > MAX_AIM_ANGLE)
        Degree = MAX_AIM_ANGLE;

    // Convertit le range de -85 à 85 vers 1 à 32
    float Frame = 32 - (Degree + MAX_AIM_ANGLE) * (31.0 / (MAX_AIM_ANGLE * 2));

    // Arrondit au nombre entier le plus proche pour obtenir l'indice de la frame
    return static_cast<int>(std::round(Frame));
}