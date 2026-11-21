/**
* @file TriangleObject.h
* @brief Definicja klasy reprezentujacej trojkat w przestrzeni 2D.
*/
#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

/**
* @class TriangleObject
* @brief Klasa reprezentujaca trojkat w przestrzeni dwuwymiarowej.
*
* Przechowuje trzy wierzcholki trojkata, jego kolor
* oraz informacje okreslajaca sposob rysowania.
*
* Umozliwia rysowanie konturu lub wypelnionego trojkata,
* a takze wykonywanie transformacji geometrycznych:
* translacji, obrotu i skalowania.
*
* Transformacje wykonywane sa na wszystkich trzech
* wierzcholkach trojkata.
*/
class TriangleObject : public ShapeObject
{
private:
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Color color;
	bool filled;

public:

	/**
	* @brief Konstruktor klasy TriangleObject.
	*
	* @param p1 Pierwszy wierzcholek trojkata.
	* @param p2 Drugi wierzcholek trojkata.
	* @param p3 Trzeci wierzcholek trojkata.
	* @param color Kolor trojkata.
	* @param filled Okresla, czy trojkat ma byc wypelniony.
	*
	* Tworzy trojkat na podstawie trzech podanych
	* wierzcholkow oraz ustawia jego kolor
	* i sposob rysowania.
	*/
	TriangleObject(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color = BLACK, bool filled = false);

	/**
	* @brief Ustawia wierzcholki trojkata.
	*
	* @param p1 Nowy pierwszy wierzcholek trojkata.
	* @param p2 Nowy drugi wierzcholek trojkata.
	* @param p3 Nowy trzeci wierzcholek trojkata.
	*
	* Metoda zastępuje wszystkie trzy wierzcholki
	* trojkata podanymi punktami.
	*/
	void SetVertices(const Point2D& p1, const Point2D& p2, const Point2D& p3) { this->p1 = p1; this->p2 = p2; this->p3 = p3; }

	/**
	* @brief Zwraca kolor trojkata.
	*
	* @return Aktualny kolor trojkata.
	*/
	Color GetColor() const { return color; }

	/**
	* @brief Ustawia kolor trojkata.
	*
	* @param color Nowy kolor trojkata.
	* @return Referencja do biezacego obiektu TriangleObject.
	*
	* Metoda umozliwia lancuchowe wywolywanie
	* metod zwracajacych referencje do obiektu.
	*/
	TriangleObject& SetColor(Color color) { this->color = color; return *this; }

	/**
	* @brief Rysuje trojkat za pomoca renderera.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	*
	* Metoda rysuje wypelniony trojkat lub jego kontur
	* w zaleznosci od wartosci pola filled.
	*
	* Do rysowania wykorzystuje zapisane wierzcholki
	* oraz kolor trojkata.
	*/
	void Draw(class PrimitiveRenderer& renderer) const override;

	/**
	* @brief Przesuwa trojkat o podany wektor.
	*
	* @param tx Przesuniecie w osi X.
	* @param ty Przesuniecie w osi Y.
	*
	* Metoda przesuwa wszystkie trzy wierzcholki
	* trojkata o podane wartosci.
	*
	* Translacja nie zmienia ksztaltu ani wymiarow trojkata.
	*/
	void Translate(float tx, float ty) override;

	/**
	* @brief Obraca trojkat wzgledem poczatku ukladu wspolrzednych.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	*
	* Metoda obraca wszystkie trzy wierzcholki
	* trojkata wzgledem punktu (0, 0).
	*
	* Obrot zmienia polozenie i orientacje trojkata,
	* zachowujac jego ksztalt oraz wymiary.
	*/
	void Rotate(float angle) override;

	/**
	* @brief Obraca trojkat wzgledem wybranego punktu.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	* @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
	*
	* Metoda obraca wszystkie trzy wierzcholki
	* trojkata wzgledem wskazanego punktu odniesienia.
	*
	* Obrot zmienia polozenie i orientacje trojkata,
	* zachowujac jego ksztalt oraz wymiary.
	*/
	void Rotate(float angle, const Point2D& origin) override;

	/**
	* @brief Skaluje trojkat wzgledem poczatku ukladu wspolrzednych.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	*
	* Metoda skaluje wszystkie trzy wierzcholki
	* trojkata wzgledem punktu (0, 0).
	*
	* Rozne wartosci wspolczynnikow kx i ky
	* umozliwiaja niezalezne skalowanie
	* w obu osiach ukladu wspolrzednych.
	*/
	void Scale(float kx, float ky) override;

	/**
	* @brief Skaluje trojkat wzgledem wybranego punktu.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	* @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
	*
	* Metoda skaluje wszystkie trzy wierzcholki
	* trojkata wzgledem wskazanego punktu odniesienia.
	*
	* Rozne wartosci wspolczynnikow kx i ky
	* umozliwiaja niezalezne skalowanie
	* w obu osiach ukladu wspolrzednych.
	*
	* @note Skalowanie nierownomierne moze zmienic proporcje i ksztalt trojkata.
	*/
	void Scale(float kx, float ky, const Point2D& origin) override;
};