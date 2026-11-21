/**
* @file TransformableObject.h
* @brief Definicja interfejsu transformacji geometrycznych obiektow.
*/
#pragma once
#include "GameObject.h"

class Point2D; // Forward declaration of Point2D class to avoid circular dependency, Point2D will be used as center of transformation


/**
* @class TransformableObject
* @brief Abstrakcyjna klasa bazowa dla obiektow podlegajacych transformacjom geometrycznym.
*
* Definiuje wspolny interfejs umozliwiajacy wykonywanie
* podstawowych transformacji geometrycznych w przestrzeni 2D.
*
* Udostepnia metody przesuwania, obracania oraz skalowania
* obiektow wzgledem poczatku ukladu wspolrzednych
* lub dowolnego punktu odniesienia.
*
* Wszystkie metody transformacji sa czysto wirtualne,
* dlatego ich implementacja nalezy do klas pochodnych.
*
* @note Klasa wykorzystuje wirtualne dziedziczenie po GameObject, aby uniknac wielokrotnego wystepowania tej klasy bazowej w hierarchii dziedziczenia.
*/
class TransformableObject : public virtual GameObject
{
public:
    /**
    * @brief Wirtualny destruktor klasy TransformableObject.
    *
    * Zapewnia prawidlowe niszczenie obiektow klas
    * pochodnych za posrednictwem wskaznika
    * do klasy bazowej.
    */
	virtual ~TransformableObject() = default;
   
    /**
    * @brief Przesuwa obiekt o podany wektor.
    *
    * @param tx Przesuniecie w osi X.
    * @param ty Przesuniecie w osi Y.
    *
    * Metoda definiuje operacje translacji obiektu
    * o wektor okreslony przez podane wartosci.
    *
    * Sposob wykonania przesuniecia zalezy
    * od implementacji w klasie pochodnej.
    */
    virtual void Translate(float tx, float ty) = 0;

    /**
    * @brief Obraca obiekt wzgledem poczatku ukladu wspolrzednych.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    *
    * Metoda definiuje operacje obrotu obiektu
    * wzgledem punktu (0, 0).
    *
    * Sposob wykonania obrotu zalezy
    * od implementacji w klasie pochodnej.
    */
    virtual void Rotate(float angle) = 0;

    /**
    * @brief Obraca obiekt wzgledem wybranego punktu.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    * @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
    *
    * Metoda definiuje operacje obrotu obiektu
    * wzgledem wskazanego punktu odniesienia.
    *
    * Sposob wykonania obrotu zalezy
    * od implementacji w klasie pochodnej.
    */
    virtual void Rotate(float angle, const Point2D& origin) = 0;

    /**
    * @brief Skaluje obiekt wzgledem poczatku ukladu wspolrzednych.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    *
    * Metoda definiuje operacje skalowania obiektu
    * wzgledem punktu (0, 0).
    *
    * Wspolczynniki skalowania moga przyjmowac
    * rozne wartosci dla poszczegolnych osi.
    *
    * Sposob wykonania skalowania zalezy
    * od implementacji w klasie pochodnej.
    */
    virtual void Scale(float kx, float ky) = 0;

    /**
    * @brief Skaluje obiekt wzgledem wybranego punktu.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    * @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
    *
    * Metoda definiuje operacje skalowania obiektu
    * wzgledem wskazanego punktu odniesienia.
    *
    * Wspolczynniki skalowania moga przyjmowac
    * rozne wartosci dla poszczegolnych osi.
    *
    * Sposob wykonania skalowania zalezy
    * od implementacji w klasie pochodnej.
    */
    virtual void Scale(float kx, float ky, const Point2D& origin) = 0;
};