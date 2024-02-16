#ifndef VECTOR_H
#define VECTOR_H

#pragma once

template <typename T>
class Vector
{
public:
    // Constructeurs
    Vector() : X(T()), Y(T()) {}
    Vector(T x, T y) : X(x), Y(y) {}

    // Destructeur
    ~Vector() {}

    // Opérateurs
    Vector<T> operator+(const Vector<T>& other) const {
        return Vector<T>(X + other.X, Y + other.Y);
    }

    // Membres publics
    T X;
    T Y;
};

#endif
