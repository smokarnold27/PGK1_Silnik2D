#pragma once
#include "GameObject.h"

class PrimitiveRenderer; // Forward declaration of PrimitiveRenderer class to avoid circular dependency

class DrawableObject : public virtual GameObject
{
public:
	// Wirtualny destruktor gwarantuje poprawne niszczenie obiektów dziedziczących
	virtual ~DrawableObject() = default;
	// Przykładowa metoda czysto wirtualna (opcjonalna, np. renderowanie obiektu)
	virtual void Draw(PrimitiveRenderer& renderer) const = 0;
};