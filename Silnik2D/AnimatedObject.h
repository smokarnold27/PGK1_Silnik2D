/**
* @file AnimatedObject.h
* 
* @brief Definicja klasy sluzacej do implementacji animacji
* 
* Plik zawiera tylko interfejs i nie ma pliku .cpp. Klasa ma byc tylko dziedziczona przez inne obiekty
* gdzie dokladna implementacja metod zostanie zaimplementowana.
*
*/

#pragma once
#include "GameObject.h"


/**
* @class AnimatedObject
* 
* @brief Klasa ktora zawiera metode sluzaca do animowania obiektow
* 
*/
class AnimatedObject : public virtual GameObject
{
public:
    /**
    * @brief Wirtualny destruktor sluzacy do zwalniania pamieci klas pochodnych
    */
    virtual ~AnimatedObject() = default;

    /**
    * @brief Animacja obiektu
    * 
    * Dokladne dzialanie zalezy od implementacji w klasie pochodnej
    */
    virtual void animate() = 0;
};