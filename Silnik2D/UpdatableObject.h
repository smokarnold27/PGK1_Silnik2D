/**
* @file UpdatableObject.h
* @brief Definicja interfejsu aktualizacji stanu obiektow.
*/
#pragma once
#include "GameObject.h"

/**
* @class UpdatableObject
* @brief Abstrakcyjna klasa bazowa dla obiektow wymagajacych aktualizacji.
*
* Definiuje wspolny interfejs umozliwiajacy aktualizowanie
* stanu obiektow podczas dzialania aplikacji.
*
* Udostepnia metode Update(), ktora moze byc
* wykorzystywana do aktualizacji polozenia,
* animacji lub innych elementow stanu obiektu.
*
* Metoda aktualizacji jest czysto wirtualna,
* dlatego jej implementacja nalezy do klas pochodnych.
*
* @note Klasa wykorzystuje wirtualne dziedziczenie po GameObject, aby uniknac wielokrotnego wystepowania tej klasy bazowej w hierarchii dziedziczenia.
*/
class UpdatableObject : public virtual GameObject
{
public:
    /**
    * @brief Wirtualny destruktor klasy UpdatableObject.
    *
    * Zapewnia prawidlowe niszczenie obiektow klas
    * pochodnych za posrednictwem wskaznika
    * do klasy bazowej.
    */
	virtual ~UpdatableObject() = default;

	/**
    * @brief Aktualizuje stan obiektu.
    *
    * @param deltaTime Czas, ktory uplynal od poprzedniej aktualizacji, wyrazony w sekundach.
    *
    * Metoda definiuje operacje aktualizacji stanu
    * obiektu na podstawie uplywu czasu.
    *
    * Moze byc wykorzystywana do obslugi ruchu,
    * animacji, logiki obiektu oraz innych
    * zmian zachodzacych podczas dzialania aplikacji.
    *
    * Sposob wykorzystania parametru deltaTime
    * zalezy od implementacji w klasie pochodnej.
    */
	virtual void Update(float deltaTime) = 0;
};