#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

class Vector
{
public:
	static void Normalized(sf::Vector2f &Vec);

	static sf::Vector2f GetDirection(sf::Vector2f VecStart, sf::Vector2f VecEnd);
	static sf::Vector2f GetDirectionVector(const float &Degrees);
	static sf::Vector2f RotateVector(const sf::Vector2f &Vector, const float &Degrees);
	static sf::Vector2f AdjustVectorLength(const sf::Vector2f &Vector, const float &NewLength);
	
	static float GetDistance(sf::Vector2f Vec1, sf::Vector2f Vec2);
	static float DotProduct(sf::Vector2f Vec1, sf::Vector2f Vec2);
	static float CrossProduct(const sf::Vector2f& u, const sf::Vector2f& v);
	static float GetAngleWithXAxis(const sf::Vector2f& Vector);

	static bool IsColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2);
	static bool IsColineaire(sf::Vector3f Vec1, sf::Vector3f Vec2);

	static bool AreColineaire(sf::Vector2f Vec1, sf::Vector2f Vec2, sf::Vector2f Vec3);
	static bool GetCartesienne(sf::Vector2f Vec1, sf::Vector2f Vec2);
	
	static bool HasMemberNull(sf::Vector3f Vec);
};

