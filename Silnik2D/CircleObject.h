/**
* @file CircleObject.h
* @brief Definicja klasy okraglego obiektu
*/

#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

/**
* @class CircleObject
* @brief Klasa reprezentujaca okrag w przestrzeni dwuwymiarowej.
*
* Umozliwia tworzenie i rysowanie okregow o okreslonym
* srodku, promieniu, kolorze oraz sposobie wypelnienia.
*
* Obiekt obsluguje transformacje geometryczne,
* takie jak przesuwanie, obracanie i skalowanie.
*/
class CircleObject : public ShapeObject
{
private:
    Point2D center;
    int radius;
    Color color;
    bool filled;

public:
    /**
    * @brief Konstruktor klasy CircleObject.
    *
    * @param center Punkt okreslajacy srodek okregu.
    * @param radius Promien okregu wyrazony w pikselach.
    * @param color Kolor okregu.
    * @param filled Okresla, czy okrag ma zostac wypelniony.
    *
    * Konstruktor tworzy obiekt reprezentujacy okrag o podanym srodku, promieniu, kolorze i sposobie wypelnienia.
    */
    CircleObject(const Point2D& center, int radius, Color color = BLACK, bool filled = false);

    /**
    * @brief Zwrot wspolrzednych srodka okregu
    * @return Punkt o wspolrzednych (xsrodka, ysrodka)
    */
    Point2D GetCenter() const { return center; }

    /**
    * @brief Ustawienie wspolrzednych srodka okregu
    * @param center Punkt ktory posluzy za srodek okregu
    */
    void SetCenter(const Point2D& center) { this->center = center; }

    /**
    * @brief Metoda zwracajaca promien okregu
    * @return promien okregu w pikselach
    */
    int GetRadius() const { return radius; }

    /**
    * @brief Ustawienie promienia okregu
    * @param radius Dlugosc promienia
    */
    void SetRadius(int radius) { this->radius = radius; }

    /**
    * @brief Metoda zwracajaca kolor okregu
    * @return kolor okregu
    */
    Color GetColor() const { return color; }

    /**
    * @brief Ustawienie koloru okregu
    * @param color Nowy kolor okregu
    * @return Referencja do biezacego obiektu
    */
    CircleObject& SetColor(Color color) { this->color = color; return *this; }

    /**
    * @brief Rysuje okrag za pomoca renderera.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    *
    * Metoda rysuje okrag na podstawie jego srodka, promienia
    * i koloru. W zaleznosci od wartosci pola filled
    * rysowany jest okrag wypelniony lub sam jego obrys.
    */
    void Draw(class PrimitiveRenderer& renderer) const override;

    /**
    * @brief Przesuwa okrag o podany wektor.
    *
    * @param tx Przesuniecie w osi X.
    * @param ty Przesuniecie w osi Y.
    *
    * Metoda przesuwa srodek okregu o podane wartosci, nie zmieniajac jego promienia.
    */
    void Translate(float tx, float ty) override;

    /**
    * @brief Obraca okrag wzgledem poczatku ukladu wspolrzednych.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    *
    * Metoda obraca srodek okregu wzgledem punktu (0, 0).
    * Promien i ksztalt okregu pozostaja bez zmian.
    */
    void Rotate(float angle) override;

    /**
    * @brief Obraca okrag wzgledem wybranego punktu.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    * @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
    *
    * Metoda obraca srodek okregu wzgledem wskazanego punktu.
    * Promien i ksztalt okregu pozostaja bez zmian.
    */
    void Rotate(float angle, const Point2D& origin) override;

    /**
    * @brief Skaluje okrag wzgledem poczatku ukladu wspolrzednych.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    *
    * Metoda skaluje wspolrzedne srodka okregu wzgledem
    * punktu (0, 0), a nastepnie zmienia jego promien
    * na podstawie wartosci bezwzglednej wspolczynnika kx.
    */
    void Scale(float kx, float ky) override;

    /**
    * @brief Skaluje okrag wzgledem wybranego punktu.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    * @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
    *
    * Metoda skaluje wspolrzedne srodka okregu wzgledem
    * wskazanego punktu, a nastepnie zmienia jego promien
    * na podstawie wartosci bezwzglednej wspolczynnika kx.
    *
    * @note Wspolczynnik ky wplywa na polozenie srodka,
    *       ale nie zmienia promienia okregu.
    */
    void Scale(float kx, float ky, const Point2D& origin) override;
};