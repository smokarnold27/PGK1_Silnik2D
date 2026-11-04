#pragma once
class GameObject
{
public:
	virtual ~GameObject() = default; // Wirtualny destruktor, aby umożliwić poprawne usuwanie obiektów pochodnych przez wskaźnik do klasy bazowej
};

