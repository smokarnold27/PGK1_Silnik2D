/**
* @file GameObject.h
* @brief Definicja klasy bazowej dla wszystkich objektow silnika
*/

#pragma once

/**
* @class GameObject
* @brief Bazowa klasa dla obiektow silnika gry 2D.
*
* Stanowi wspolny interfejs dla klas dziedziczacych.
* Udostepnia wirtualny destruktor oraz metode
* umozliwiajaca inicjalizacje obiektu.
*/
class GameObject
{
public:
    /**
    * @brief Wirtualny destruktor klasy GameObject.
    *
    * Zapewnia poprawne wywolywanie destruktorow
    * klas pochodnych podczas usuwania obiektow
    * przez wskaznik do klasy bazowej.
    */
    virtual ~GameObject() = default;

    
    /**
    * @brief Wirtualna metoda inicjujaca obiekt
    * 
    *
    * Moze zostac nadpisana w klasach pochodnych
    * w celu wykonania dodatkowej inicjalizacji.
    *
    * Domyslna implementacja nie wykonuje zadnych operacji.
    */
    virtual void Init() {}
};