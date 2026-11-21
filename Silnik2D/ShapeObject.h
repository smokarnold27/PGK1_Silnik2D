/**
* @file ShapeObject.h
* @brief Definicja klasy bazowej dla obiektow geometrycznych 2D.
*/

#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"

/**
* @class ShapeObject
* @brief Abstrakcyjna klasa bazowa dla obiektow geometrycznych.
*
* Laczy interfejsy DrawableObject i TransformableObject,
* zapewniajac wspolna podstawe dla figur geometrycznych,
* ktore mozna rysowac i poddawac transformacjom.
*
* Klasy pochodne implementuja metody rysowania
* oraz transformacji geometrycznych zdefiniowane
* w dziedziczonych interfejsach.
*/
class ShapeObject : public DrawableObject, public TransformableObject
{
public:
    /**
    * @brief Wirtualny destruktor klasy ShapeObject.
    *
    * Zapewnia prawidlowe niszczenie obiektow klas
    * pochodnych za posrednictwem wskaznika
    * do klasy bazowej.
    */
	virtual ~ShapeObject() = default;
};