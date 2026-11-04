
#include "GameObject.h"
class UpdatableObject :
    virtual public GameObject
{
public:
	virtual ~UpdatableObject() = default; // Wirtualny destruktor, aby umożliwić poprawne usuwanie obiektów pochodnych przez wskaźnik do klasy bazowej
	virtual void Update(float deltaTime) = 0; // Metoda czysto wirtualna, która musi być zaimplementowana w klasach pochodnych
};
