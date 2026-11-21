/**
* @file Point2D.h
* @brief Definicja klasy reprezentujacej punkt w przestrzeni 2D.
*/

#pragma once
#include "ShapeObject.h"
#include "raylib.h"

/**
* @class Point2D
* @brief Klasa reprezentujaca punkt w przestrzeni dwuwymiarowej.
*
* Przechowuje wspolrzedne punktu w postaci liczb
* zmiennoprzecinkowych oraz jego kolor.
*
* Umozliwia pobieranie i modyfikowanie wspolrzednych,
* rysowanie punktu oraz wykonywanie transformacji
* geometrycznych, takich jak przesuwanie, obracanie
* i skalowanie.
*/
class Point2D : public ShapeObject
{
private:
	float x = 0.0f;
	float y = 0.0f;
	Color color;

public:

	/**
	* @brief Konstruktor klasy Point2D.
	*
	* @param x Wspolrzedna X punktu.
	* @param y Wspolrzedna Y punktu.
	* @param color Kolor punktu.
	*
	* Tworzy punkt o podanych wspolrzednych i kolorze.
	*/
	Point2D(float x = 0.0f, float y = 0.0f, Color color = BLACK);


	/**
	* @brief Zwraca zaokraglona wspolrzedna X punktu.
	*
	* @return Wspolrzedna X zaokraglona do najblizszej wartosci calkowitej.
	*/
	int GetX() const;

	/**
	* @brief Zwraca zaokraglona wspolrzedna Y punktu.
	*
	* @return Wspolrzedna Y zaokraglona do najblizszej wartosci calkowitej.
	*/
	int GetY() const;

	/**
	* @brief Zwraca dokladna wspolrzedna X punktu.
	*
	* @return Wspolrzedna X w postaci liczby zmiennoprzecinkowej.
	*/
	float GetExactX() const { return x; }

	/**
	* @brief Zwraca dokladna wspolrzedna Y punktu.
	*
	* @return Wspolrzedna Y w postaci liczby zmiennoprzecinkowej.
	*/
	float GetExactY() const { return y; }


	/**
	* @brief Ustawia wspolrzedna X punktu.
	*
	* @param x Nowa wspolrzedna X punktu.
	* @return Referencja do biezacego obiektu Point2D.
	*/
	Point2D& SetX(float x);

	/**
	* @brief Ustawia wspolrzedna Y punktu.
	*
	* @param y Nowa wspolrzedna Y punktu.
	* @return Referencja do biezacego obiektu Point2D.
	*/
	Point2D& SetY(float y);

	/**
	* @brief Zwraca kolor punktu.
	*
	* @return Aktualny kolor punktu.
	*/
	Color GetColor() const { return color; }

	/**
	* @brief Ustawia kolor punktu.
	*
	* @param color Nowy kolor punktu.
	* @return Referencja do biezacego obiektu Point2D.
	*/
	Point2D& SetColor(Color color) { this->color = color; return *this; }

	/**
	* @brief Rysuje punkt przy uzyciu wskazanego koloru.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	* @param color Kolor, ktory zostanie wykorzystany do narysowania punktu.
	*
	* Metoda rysuje pojedynczy piksel w miejscu okreslonym
	* przez zaokraglone wspolrzedne punktu.
	*
	* @note Podany kolor nie zmienia koloru zapisanego w obiekcie.
	*/
	void DrawPoint(class PrimitiveRenderer& renderer, Color color) const; 

	/**
	* @brief Rysuje punkt za pomoca renderera.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	*
	* Metoda rysuje pojedynczy piksel w miejscu okreslonym
	* przez zaokraglone wspolrzedne punktu, wykorzystujac
	* kolor zapisany w obiekcie.
	*/
	void Draw(PrimitiveRenderer& renderer) const override;

	/**
	* @brief Przesuwa punkt o podany wektor.
	*
	* @param tx Przesuniecie w osi X.
	* @param ty Przesuniecie w osi Y.
	*
	* Metoda dodaje podane wartosci do aktualnych
	* wspolrzednych punktu.
	*/
	void Translate(float tx, float ty) override; // Implementacja translacji z klasy TransformableObject

	/**
	* @brief Obraca punkt wzgledem poczatku ukladu wspolrzednych.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	*
	* Metoda oblicza nowe wspolrzedne punktu
	* na podstawie kata obrotu wzgledem punktu (0, 0).
	*/
	void Rotate(float angle) override; // Implementacja rotacji z klasy TransformableObject

	/**
	* @brief Obraca punkt wzgledem wybranego punktu.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	* @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
	*
	* Metoda oblicza nowe wspolrzedne punktu
	* na podstawie kata obrotu i wskazanego
	* srodka obrotu.
	*/
	void Rotate(float angle, const Point2D& origin) override; // Implementacja rotacji względem punktu z klasy TransformableObject

	/**
	* @brief Skaluje punkt wzgledem poczatku ukladu wspolrzednych.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	*
	* Metoda mnozy wspolrzedna X przez kx,
	* a wspolrzedna Y przez ky.
	*/
	void Scale(float kx, float ky) override; // Implementacja skalowania z klasy TransformableObject

	/**
	* @brief Skaluje punkt wzgledem wybranego punktu.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	* @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
	*
	* Metoda skaluje wspolrzedne punktu wzgledem
	* wskazanego punktu odniesienia, wykorzystujac
	* niezalezne wspolczynniki dla osi X i Y.
	*/
	void Scale(float kx, float ky, const Point2D& origin) override; // Implementacja skalowania względem punktu z klasy TransformableObject
};
