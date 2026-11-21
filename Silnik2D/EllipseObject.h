/**
* @filename EllipseObject.h
* @brief Definicja klasy obiektu elipsy
*/

#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

/**
* @class EllipseObject
* @brief Klasa reprezentujaca elipse w przestrzeni dwuwymiarowej.
*
* Umozliwia tworzenie i rysowanie elips o okreslonym srodku, promieniach, kolorze oraz sposobie wypelnienia.
*
* Obiekt obsluguje transformacje geometryczne, takie jak przesuwanie i skalowanie.
*/
class EllipseObject : public ShapeObject
{
private:
    Point2D center;
    int radiusX;
    int radiusY;
    Color color;
    bool filled;

public:
    /**
    * @brief Konstruktor klasy EllipseObject.
    *
    * @param center Punkt okreslajacy srodek elipsy.
    * @param radiusX Promien elipsy w osi X, wyrazony w pikselach.
    * @param radiusY Promien elipsy w osi Y, wyrazony w pikselach.
    * @param color Kolor elipsy.
    * @param filled Okresla, czy elipsa ma zostac wypelniona.
    *
    * Konstruktor tworzy obiekt reprezentujacy elipse
    * o podanym srodku, promieniach, kolorze i sposobie wypelnienia.
    */
    EllipseObject(const Point2D& center, int radiusX, int radiusY, Color color = BLACK, bool filled = false);

    /**
    * @brief Zwrot srodka elipsy
    * @return Wspolrzedne srodka elipsy
    */
    Point2D GetCenter() const { return center; }

    /**
    * @brief Ustawienie srodka elipsy
    * @param center Wspolrzedne srodka elipsy
    */
    void SetCenter(const Point2D& center) { this->center = center; }

    /**
    * @brief Zwrot koloru elipsy
    * @return Kolor elipsy
    */
    Color GetColor() const { return color; }

    /**
    * @brief Ustawienie koloru elipsy
    * @param color Kolor elipsy
    * @return Referencja do biezacego obiektu
    */
    EllipseObject& SetColor(Color color) { this->color = color; return *this; }

    /**
    * @brief Rysuje elipse za pomoca renderera.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    *
    * Metoda rysuje elipse na podstawie jej srodka,
    * promieni i koloru. W zaleznosci od wartosci pola
    * filled rysowana jest elipsa wypelniona lub jej obrys.
    */
    void Draw(class PrimitiveRenderer& renderer) const override;

    /**
    * @brief Przesuwa elipse o podany wektor.
    *
    * @param tx Przesuniecie w osi X.
    * @param ty Przesuniecie w osi Y.
    *
    * Metoda przesuwa srodek elipsy o podane wartosci, nie zmieniajac jej promieni.
    */
    void Translate(float tx, float ty) override;

    /**
    * @brief Obraca srodek elipsy wzgledem poczatku ukladu wspolrzednych.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    *
    * Metoda obraca srodek elipsy wzgledem punktu (0, 0).
    * Nie zmienia promieni ani orientacji samej elipsy.
    */
    void Rotate(float angle) override;

    /**
    * @brief Obraca srodek elipsy wzgledem wybranego punktu.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    * @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
    *
    * Metoda obraca srodek elipsy wzgledem wskazanego punktu.
    * Nie zmienia promieni ani orientacji samej elipsy.
    */
    void Rotate(float angle, const Point2D& origin) override;

    /**
    * @brief Skaluje elipse wzgledem poczatku ukladu wspolrzednych.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    *
    * Metoda zmienia promien poziomy na podstawie wartosci
    * bezwzglednej wspolczynnika kx, a promien pionowy
    * na podstawie wartosci bezwzglednej wspolczynnika ky.
    * Dodatkowo skaluje wspolrzedne srodka elipsy
    * wzgledem punktu (0, 0).
    */
    void Scale(float kx, float ky) override;

    /**
    * @brief Skaluje elipse wzgledem wybranego punktu.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    * @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
    *
    * Metoda zmienia promien poziomy na podstawie wartosci
    * bezwzglednej wspolczynnika kx, a promien pionowy
    * na podstawie wartosci bezwzglednej wspolczynnika ky.
    * Dodatkowo skaluje wspolrzedne srodka elipsy
    * wzgledem wskazanego punktu.
    */
    void Scale(float kx, float ky, const Point2D& origin) override;
};