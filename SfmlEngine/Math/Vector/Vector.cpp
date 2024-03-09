#include "Vector.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846 /* pi */

void Vector::Normalized(sf::Vector2f &Vec)
{
	// Calculer la longueur du vecteur
	float length = std::sqrt(Vec.x * Vec.x + Vec.y * Vec.y);

	// Assurer que la longueur n'est pas nulle pour éviter la division par zéro
	if (length != 0)
	{
		// Normaliser le vecteur en divisant chaque composante par sa longueur
		Vec = sf::Vector2f(Vec.x / length, Vec.y / length);
	}
}

sf::Vector2f Vector::GetDirection(sf::Vector2f VecStart, sf::Vector2f VecEnd)
{
	sf::Vector2f Direction = (VecEnd - VecStart);
	Normalized(Direction);
	return Direction;
}

sf::Vector2f Vector::GetDirectionVector(const float &Degrees)
{
	// Convertir l'angle en radians
	float Radians = Degrees * 3.14159265358979323846 / 180.0;

	// Calculer les composantes x et y du vecteur direction
	float X = std::cos(Radians);
	float Y = std::sin(Radians);

	return sf::Vector2f(X, Y);
}

sf::Vector2f Vector::AdjustVectorLength(const sf::Vector2f &Vector, const float &NewLength)
{
	// Normaliser le vecteur direction
	sf::Vector2f NormalizedVector = Vector / std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y);

	// Multiplier le vecteur normalisé par la nouvelle longueur
	return NormalizedVector * NewLength;
}

sf::Vector2f Vector::RotateVector(const sf::Vector2f &Vector, const float &Degrees)
{
	// Convertir l'angle en radians
	float Radians = Degrees * 3.14159265358979323846 / 180.0;

	// Calculer les composantes x et y du vecteur après la rotation
	float newX = Vector.x * std::cos(Radians) - Vector.y * std::sin(Radians);
	float newY = Vector.x * std::sin(Radians) + Vector.y * std::cos(Radians);

	sf::Vector2f NewVector = sf::Vector2f(newX, newY);
	// Normalized(NewVector);
	return NewVector;
}

float Vector::GetDistance(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	return sqrt(pow(Vec1.x - Vec2.x, 2) + pow(Vec1.y - Vec2.y, 2));
}

float Vector::DotProduct(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	float normeV1 = sqrt(pow(Vec1.x, 2) + pow(Vec1.y, 2));
	float normeV2 = sqrt(pow(Vec2.x, 2) + pow(Vec2.y, 2));

	float ps = Vec1.x * Vec2.x + Vec1.y * Vec2.y;

	float deg;
	deg = ps / (normeV1 * normeV2);
	deg = acos(deg) * 180 / PI;

	return deg;
}

float Vector::CrossProduct(const sf::Vector2f &u, const sf::Vector2f &v)
{
	return u.x * v.y - u.y * v.x;
}

bool Vector::IsColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2)
{
	float val = Vec1.x * Vec2.y - Vec2.x * Vec1.y;
	if (val == 0)
		return true;
	return false;
}

bool Vector::IsColineaire(sf::Vector3f Vec1, sf::Vector3f Vec2)
{
	if (HasMemberNull(Vec1) || HasMemberNull(Vec2))
		return false;

	return false;
}

bool Vector::AreColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2, sf::Vector2f Vec3)
{
	if (!IsColineaire(Vec1, Vec2))
		return false;
	else if (!IsColineaire(Vec1, Vec3))
		return false;

	return true;
}

bool Vector::GetCartesienne(sf::Vector2f Vec1, sf::Vector2f Vec2)
{

	return true;
}

bool Vector::HasMemberNull(sf::Vector3f Vec)
{
	if (Vec.x == 0 || Vec.y == 0 || Vec.z == 0)
		return true;
	return false;
}
