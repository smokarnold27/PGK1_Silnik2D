#pragma once
#include "GameObject.h"
class TransformableObject :
    virtual public GameObject
{
public:
	virtual ~TransformableObject() = default; // Wirtualny destruktor, aby umożliwić poprawne usuwanie obiektów pochodnych przez wskaźnik do klasy bazowej
	virtual void Translate(float dx, float dy) = 0; // Metoda czysto wirtualna, która musi być zaimplementowana w klasach pochodnych
	virtual void Rotate(float angle) = 0; // Metoda czysto wirtualna, która musi być zaimplementowana w klasach pochodnych
	virtual void Scale(float sx, float sy) = 0; // Metoda czysto wirtualna, która musi być zaimplementowana w klasach pochodnych
};

