/**
* @file DrawableObject.h
* @brief Definicja klasy zawierajaca funkcje sluzaca do wyswietlania obiektow na ekranie
*/
#pragma once
#include "GameObject.h"

class PrimitiveRenderer; // Forward declaration of PrimitiveRenderer class to avoid circular dependency

/**
* @class DrawableObject
* 
* @brief Klasa sluzaca do rysowania rzeczy w oknie
* 
* Ta klasa sama w sobie nie ma zadnej implementacji, zawiera jedynie funkcje Draw(), ktora
* bedzie wykorzystywana przez klasy pochodne.
*/
class DrawableObject : public virtual GameObject
{
public:
	
	/**
	* @brief Wirtualny destruktor
	* 
	* Wirtualny destruktor gwarantuje poprawne niszczenie obiektow dziedziczacych
	*/
	virtual ~DrawableObject() = default;

	/**
	* @brief Metoda sluzaca do rysowania obiektow
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	* 
	* Wzorzec metody sluzacej do wyswietlenia danego obiektu na ekran, implementacja zalezy od klasy pochodnej
	*/
	virtual void Draw(PrimitiveRenderer& renderer) const = 0;
};