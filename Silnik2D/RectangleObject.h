/**
* @file RectangleObject.h
* @brief Definicja klasy reprezentujacej prostokat w przestrzeni 2D.
*/

#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

/**
* @class RectangleObject
* @brief Klasa reprezentujaca prostokat w przestrzeni dwuwymiarowej.
*
* Przechowuje punkt odniesienia prostokata, jego szerokosc,
* wysokosc, kolor oraz informacje o wypelnieniu.
*
* Umozliwia rysowanie prostokata wypelnionego lub jego
* konturu, a takze wykonywanie transformacji geometrycznych.
*
* Boki prostokata pozostaja rownolegle do osi
* ukladu wspolrzednych.
*
* @note Obracanie prostokata zmienia polozenie jego punktu odniesienia, ale nie orientacje bokow.
*/
class RectangleObject : public ShapeObject
{
private:
	Point2D topLeft;
	float width;
	float height;
	Color color;
	bool filled;

public:
	/**
	* @brief Konstruktor klasy RectangleObject.
	*
	* @param topLeft Punkt odniesienia prostokata.
	* @param width Szerokosc prostokata.
	* @param height Wysokosc prostokata.
	* @param color Kolor prostokata.
	* @param filled Okresla, czy prostokat ma byc wypelniony.
	*
	* Tworzy prostokat o podanych wymiarach,
	* polozeniu, kolorze i sposobie rysowania.
	*/
	RectangleObject(const Point2D& topLeft, float width, float height, Color color = BLACK, bool filled = false);

	/**
	* @brief Zwraca punkt odniesienia prostokata.
	*
	* @return Kopia punktu topLeft.
	*/
	Point2D GetTopLeft() const { return topLeft; }

	/**
	* @brief Ustawia punkt odniesienia prostokata.
	*
	* @param p Nowy punkt odniesienia prostokata.
	*/
	void SetTopLeft(const Point2D& p) { topLeft = p; }

	/**
	* @brief Zwraca kolor prostokata.
	*
	* @return Aktualny kolor prostokata.
	*/
	Color GetColor() const { return color; }

	/**
	* @brief Ustawia kolor prostokata.
	*
	* @param color Nowy kolor prostokata.
	* @return Referencja do biezacego obiektu RectangleObject.
	*/
	RectangleObject& SetColor(Color color) { this->color = color; return *this; }

	/**
	* @brief Zwraca szerokosc prostokata.
	*
	* @return Aktualna szerokosc prostokata.
	*/
	float GetWidth() const { return width; }

	/**
	* @brief Zwraca wysokosc prostokata.
	*
	* @return Aktualna wysokosc prostokata.
	*/
	float GetHeight() const { return height; }

	/**
	* @brief Rysuje prostokat za pomoca renderera.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	*
	* Metoda rysuje wypelniony prostokat lub jego kontur,
	* w zaleznosci od wartosci pola filled.
	*
	* Do rysowania wykorzystuje punkt odniesienia,
	* wymiary oraz kolor zapisane w obiekcie.
	*
	* @note Wymiary prostokata sa konwertowane z typu float na typ int przed rysowaniem.
	*/
	void Draw(class PrimitiveRenderer& renderer) const override;

	/**
	* @brief Przesuwa prostokat o podany wektor.
	*
	* @param tx Przesuniecie w osi X.
	* @param ty Przesuniecie w osi Y.
	*
	* Metoda przesuwa punkt odniesienia prostokata
	* o podane wartosci, nie zmieniajac jego wymiarow.
	*/
	void Translate(float tx, float ty) override;

	/**
	* @brief Obraca punkt odniesienia prostokata wzgledem poczatku ukladu wspolrzednych.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	*
	* Metoda obraca punkt topLeft wzgledem punktu (0, 0).
	*
	* @note Orientacja prostokata i jego wymiary pozostaja niezmienione.
	*/
	void Rotate(float angle) override;

	/**
	* @brief Obraca punkt odniesienia prostokata wzgledem wybranego punktu.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	* @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
	*
	* Metoda obraca punkt topLeft wzgledem
	* wskazanego punktu odniesienia.
	*
	* @note Orientacja prostokata i jego wymiary pozostaja niezmienione.
	*/
	void Rotate(float angle, const Point2D& origin) override;

	/**
	* @brief Skaluje prostokat wzgledem poczatku ukladu wspolrzednych.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	*
	* Metoda mnozy szerokosc i wysokosc prostokata
	* przez odpowiednie wspolczynniki skalowania
	* oraz skaluje punkt topLeft wzgledem punktu (0, 0).
	*/
	void Scale(float kx, float ky) override;

	/**
	* @brief Skaluje prostokat wzgledem wybranego punktu.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	* @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
	*
	* Metoda mnozy szerokosc i wysokosc prostokata
	* przez odpowiednie wspolczynniki skalowania
	* oraz skaluje punkt topLeft wzgledem
	* wskazanego punktu odniesienia.
	*/
	void Scale(float kx, float ky, const Point2D& origin) override;
};