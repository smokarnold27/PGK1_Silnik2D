/**
* @file LineSegment.h
* @brief Definicja klasy sluzacej do rysowania odcinkow
*/

#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

/**
* @enum LineAlgorithm
* @brief Dostepne algorytmy rysowania odcinkow.
*
* Typ wyliczeniowy okreslajacy algorytm wykorzystywany podczas rysowania odcinka.
*/
enum class LineAlgorithm {
	/** @brief Algorytm przyrostowy DDA. */
    DDA,        
	/** @brief Algorytm Bresenhama. */
    Bresenham
};

/**
* @class LineSegment
* @brief Klasa reprezentujaca odcinek w przestrzeni dwuwymiarowej.
*
* Odcinek jest okreslony przez dwa punkty koncowe,
* kolor oraz algorytm wykorzystywany do jego rysowania.
*
* Klasa umozliwia rysowanie odcinka z wykorzystaniem
* algorytmu DDA lub Bresenhama, a takze wykonywanie
* transformacji geometrycznych, takich jak
* przesuwanie, obracanie i skalowanie.
*/

class LineSegment : public ShapeObject
{
private:
	Point2D startPoint;
	Point2D endPoint;
    Color color;
	LineAlgorithm defaultAlgorithm; // Domyślny algorytm rysowania lini

public:
	/**
	* @brief Konstruktor klasy LineSegment wykorzystujacy dwa punkty.
	*
	* @param p1 Punkt poczatkowy odcinka.
	* @param p2 Punkt koncowy odcinka.
	* @param color Kolor odcinka.
	* @param algorithm Algorytm wykorzystywany do rysowania odcinka.
	*
	* Tworzy odcinek pomiedzy wskazanymi punktami,
	* przypisujac mu okreslony kolor i algorytm rysowania.
	*/
    LineSegment(const Point2D& p1 = Point2D(0, 0), const Point2D& p2 = Point2D(0, 0), Color color = BLACK, LineAlgorithm algorithm = LineAlgorithm::DDA);

	/**
	* @brief Konstruktor klasy LineSegment wykorzystujacy wspolrzedne punktow.
	*
	* @param x1 Wspolrzedna X punktu poczatkowego.
	* @param y1 Wspolrzedna Y punktu poczatkowego.
	* @param x2 Wspolrzedna X punktu koncowego.
	* @param y2 Wspolrzedna Y punktu koncowego.
	* @param color Kolor odcinka.
	* @param algorithm Algorytm wykorzystywany do rysowania odcinka.
	*
	* Tworzy odcinek na podstawie wspolrzednych
	* jego punktow koncowych, przypisujac mu
	* okreslony kolor i algorytm rysowania.
	*/
    LineSegment(float x1, float y1, float x2, float y2, Color color = BLACK, LineAlgorithm algorithm = LineAlgorithm::DDA);

	/**
	* @brief Pobranie wspolrzednych poczatku odcinka
	* @return Punkt startowy odcinka
	*/
	Point2D GetStartPoint() const { return startPoint; }

	/**
	* @brief Pobranie wspolrzednych konca odcinka
	* @return Punkt koncowy odcinka
	*/
    Point2D GetEndPoint() const { return endPoint; }

	/**
	* @brief Ustawia punkt poczatkowy odcinka.
	*
	* @param p Nowy punkt poczatkowy odcinka.
	*/
	void SetStartPoint(const Point2D& p) { startPoint = p; }

	/**
	* @brief Ustawia punkt koncowy odcinka.
	*
	* @param p Nowy punkt koncowy odcinka.
	*/
    void SetEndPoint(const Point2D& p) { endPoint = p; }

	/**
	* @brief Ustawia oba punkty koncowe odcinka.
	*
	* @param p1 Nowy punkt poczatkowy odcinka.
	* @param p2 Nowy punkt koncowy odcinka.
	*/
    void SetSegment(const Point2D& p1, const Point2D& p2) { startPoint = p1; endPoint = p2; }
    
	/**
	* @brief Zwraca kolor odcinka.
	*
	* @return Aktualny kolor odcinka.
	*/
	Color GetColor() const { return color; }

	/**
	* @brief Ustawia kolor odcinka.
	*
	* @param color Nowy kolor odcinka.
	* @return Referencja do biezacego obiektu LineSegment.
	*/
	LineSegment& SetColor(Color color) { this->color = color; return *this; }


	/**
	* @brief Rysuje odcinek za pomoca wybranego algorytmu.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	*
	* Metoda rysuje odcinek pomiedzy jego punktami koncowymi,
	* wykorzystujac przypisany kolor i algorytm rysowania.
	*
	* Dla wartosci LineAlgorithm::DDA wykorzystywany jest
	* algorytm przyrostowy DDA. W pozostalych przypadkach
	* wykorzystywany jest algorytm Bresenhama.
	*/
    void Draw(class PrimitiveRenderer& renderer) const override;
	

	/**
	* @brief Przesuwa odcinek o podany wektor.
	*
	* @param tx Przesuniecie w osi X.
	* @param ty Przesuniecie w osi Y.
	*
	* Metoda przesuwa oba punkty koncowe odcinka
	* o podane wartosci, zachowujac jego dlugosc
	* i orientacje.
	*/
	void Translate(float tx, float ty) override;

	/**
	* @brief Obraca odcinek wzgledem poczatku ukladu wspolrzednych.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	*
	* Metoda obraca oba punkty koncowe odcinka wzgledem punktu (0, 0).
	*/
	void Rotate(float angle) override;

	/**
	* @brief Obraca odcinek wzgledem wybranego punktu.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	* @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
	*
	* Metoda obraca oba punkty koncowe odcinka wzgledem wskazanego punktu.
	*/
	void Rotate(float angle, const Point2D& origin) override;

	/**
	* @brief Skaluje odcinek wzgledem poczatku ukladu wspolrzednych.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	*
	* Metoda skaluje wspolrzedne obu punktow koncowych odcinka wzgledem punktu (0, 0).
	*
	* Skalowanie moze zmienic dlugosc i orientacje odcinka.
	*/
	void Scale(float kx, float ky) override;

	/**
	* @brief Skaluje odcinek wzgledem wybranego punktu.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	* @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
	*
	* Metoda skaluje wspolrzedne obu punktow koncowych odcinka wzgledem wskazanego punktu.
	*
	* Skalowanie moze zmienic dlugosc i orientacje odcinka.
	*/
	void Scale(float kx, float ky, const Point2D& origin) override;
};

