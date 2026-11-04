#pragma once
#include "GameObject.h"
class DrawableObject :
    virtual public GameObject
{
public:
	virtual ~DrawableObject() = default; // Wirtualny destruktor, aby umożliwić poprawne usuwanie obiektów pochodnych przez wskaźnik do klasy bazowej
	virtual void Draw() const = 0; // Metoda czysto wirtualna, która musi być zaimplementowana w klasach pochodnych
};

