#pragma once
#include "GameObject.h"

class UpdatableObject : public virtual GameObject
{
public:
	// Wirtualny destruktor gwarantuje poprawne niszczenie obiektów dziedziczących
	virtual ~UpdatableObject() = default;
	// Przykładowa metoda czysto wirtualna (opcjonalna, np. aktualizacja stanu obiektu)
	virtual void Update(float deltaTime) = 0;
};