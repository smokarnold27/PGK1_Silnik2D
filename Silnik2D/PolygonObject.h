/**
* @file PolygonObject.h
* @brief Definicja klasy reprezentujacej wielokat w przestrzeni 2D.
*/

#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"
#include <vector>

/**
* @class PolygonObject
* @brief Klasa reprezentujaca wielokat w przestrzeni dwuwymiarowej.
*
* Przechowuje zbior punktow okreslajacych wierzcholki
* wielokata oraz jego kolor, sposob wypelnienia
* i informacje o zamknieciu konturu.
*
* Umozliwia rysowanie wielokata wypelnionego
* lub jego obrysu, a takze wykonywanie transformacji
* geometrycznych na wszystkich jego wierzcholkach.
*/
class PolygonObject : public ShapeObject
{
private:
    std::vector<Point2D> points;
    Color color;
    bool filled;
    bool closed;

public:

    /**
    * @brief Konstruktor klasy PolygonObject.
    *
    * @param points Wektor punktow okreslajacych wierzcholki wielokata.
    * @param color Kolor wielokata.
    * @param filled Okresla, czy wielokat ma zostac wypelniony.
    * @param closed Okresla, czy kontur wielokata ma byc zamkniety.
    *
    * Tworzy obiekt reprezentujacy wielokat na podstawie
    * podanych wierzcholkow oraz ustawien rysowania.
    */
    PolygonObject(const std::vector<Point2D>& points, Color color = BLACK, bool filled = false, bool closed = true);


    /**
    * @brief Zwraca wierzcholki wielokata.
    *
    * @return Stala referencja do wektora punktow okreslajacych wierzcholki wielokata.
    *
    * Zwracana referencja umozliwia odczyt punktow bez kopiowania calego wektora.
    */
    const std::vector<Point2D>& GetPoints() const { return points; }

    /**
    * @brief Ustawia wierzcholki wielokata.
    *
    * @param points Nowy wektor punktow okreslajacych wierzcholki wielokata.
    *
    * Metoda zastepuje dotychczasowe wierzcholki wielokata nowym zestawem punktow.
    */
    void SetPoints(const std::vector<Point2D>& points) { this->points = points; }

    /**
    * @brief Zwraca kolor wielokata.
    *
    * @return Aktualny kolor wielokata.
    */
    Color GetColor() const { return color; }

    /**
    * @brief Ustawia kolor wielokata.
    *
    * @param color Nowy kolor wielokata.
    * @return Referencja do biezacego obiektu PolygonObject.
    */
    PolygonObject& SetColor(Color color) { this->color = color; return *this; }

    /**
    * @brief Rysuje wielokat za pomoca renderera.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    *
    * Metoda rysuje wielokat na podstawie jego wierzcholkow
    * oraz przypisanego koloru.
    *
    * Jesli wielokat jest zamkniety i ma wlaczone wypelnienie,
    * rysowany jest jako figura wypelniona.
    *
    * W pozostalych przypadkach rysowana jest lamana,
    * ktorej kontur moze byc otwarty lub zamkniety.
    *
    * @note Wypelnienie jest wykonywane tylko wtedy, gdy pola filled i closed maja wartosc true.
    */
    void Draw(class PrimitiveRenderer& renderer) const override;

    /**
    * @brief Przesuwa wielokat o podany wektor.
    *
    * @param tx Przesuniecie w osi X.
    * @param ty Przesuniecie w osi Y.
    *
    * Metoda przesuwa wszystkie wierzcholki wielokata
    * o podane wartosci.
    */
    void Translate(float tx, float ty) override;

    /**
    * @brief Obraca wielokat wzgledem poczatku ukladu wspolrzednych.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    *
    * Metoda obraca wszystkie wierzcholki wielokata
    * wzgledem punktu (0, 0).
    */
    void Rotate(float angle) override;

    /**
    * @brief Obraca wielokat wzgledem wybranego punktu.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    * @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
    *
    * Metoda obraca wszystkie wierzcholki wielokata
    * wzgledem wskazanego punktu.
    */
    void Rotate(float angle, const Point2D& origin) override;

    /**
    * @brief Skaluje wielokat wzgledem poczatku ukladu wspolrzednych.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    *
    * Metoda skaluje wspolrzedne wszystkich wierzcholkow
    * wielokata wzgledem punktu (0, 0).
    */
    void Scale(float kx, float ky) override;

    /**
    * @brief Skaluje wielokat wzgledem wybranego punktu.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    * @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
    *
    * Metoda skaluje wspolrzedne wszystkich wierzcholkow
    * wielokata wzgledem wskazanego punktu.
    */
    void Scale(float kx, float ky, const Point2D& origin) override;
};