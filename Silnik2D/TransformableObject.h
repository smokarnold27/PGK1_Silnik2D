#pragma once
#include "GameObject.h"

class Point2D; // Forward declaration of Point2D class to avoid circular dependency, Point2D will be used as center of transformation

class TransformableObject : public virtual GameObject
{
public:
	// Wirtualny destruktor gwarantuje poprawne niszczenie obiektów dziedziczących
	virtual ~TransformableObject() = default;
   
    // 1. Translacja (przesunięcie o wektor [tx, ty])
    virtual void Translate(float tx, float ty) = 0;

    // 2. Rotacja (obrót o kąt angle w radianach względem (0,0) oraz względem dowolnego punktu origin)
    virtual void Rotate(float angle) = 0;
    virtual void Rotate(float angle, const Point2D& origin) = 0;

    // 3. Skalowanie / jednokładność (względem (0,0) oraz względem dowolnego punktu origin)
    virtual void Scale(float kx, float ky) = 0;
    virtual void Scale(float kx, float ky, const Point2D& origin) = 0;
};