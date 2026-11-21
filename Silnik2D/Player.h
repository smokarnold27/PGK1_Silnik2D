/**
* @file Player.h
* @brief Definicja klasy reprezentujacej obiekt gracza.
*/

#pragma once
#include "SpriteObject.h"
#include "UpdatableObject.h"
#include "Point2D.h"
#include "raylib.h"


/**
* @class Player
* @brief Klasa reprezentujaca sterowany obiekt gracza.
*
* Klasa umozliwia obsluge ruchu gracza na podstawie
* wejscia z klawiatury, aktualizacje jego stanu
* oraz rysowanie z wykorzystaniem animowanych sprite'ow.
*
* Obiekt przechowuje informacje o pozycji, rozmiarze,
* kolorze i predkosci poruszania sie.
*
* Klasa wykorzystuje mechanizmy klasy SpriteObject
* do zarzadzania animacja oraz klasy BitmapObject
* do wykonywania transformacji geometrycznych.
*/
class Player : public SpriteObject, public UpdatableObject
{
private:
	Point2D pos; //POZYCJA GRACZA
	int speed; //PREDKOSC/O ILE PIKSELI GRACZ PRZESUWA SIE PRZY POJEDYNCZYM RUCHU
	int size; //ROZMIAR GRACZA
	Color color; //KOLOR GRACZA
	int kierunek = 0; // 0-przod, 1-tyl, 2-prawo, 3-lewo

public:

	/**
	* @brief Konstruktor klasy Player.
	*
	* @param pos Poczatkowa pozycja gracza.
	* @param size Rozmiar gracza wykorzystywany przy rysowaniu zastepczym.
	* @param color Kolor gracza wykorzystywany przy rysowaniu zastepczym.
	* @param speed Predkosc poruszania sie gracza.
	*
	* Konstruktor inicjalizuje podstawowe wlasciwosci gracza,
	* konfiguruje animacje sprite'ow oraz wczytuje bitmapy
	* odpowiadajace poszczegolnym kierunkom ruchu.
	*
	* Ustawia rowniez poczatkowa pozycje i skale obiektu graficznego.
	*/
	Player(const Point2D& pos, int size, Color color = BLACK, int speed = 2);

	/**
	* @brief Zwrot pozycji gracza
	* @return Punkt2D w ktorym znajduje sie gracz
	*/
	Point2D GetPosition() const { return pos; }

	/**
	* @brief Ustawienie nowej pozycji gracza
	* @param pos Punkt zawierajacy wspolrzedne nowej pozycji
	*/
	void SetPosition(const Point2D& pos) { this->pos = pos; }

	/**
	* @brief Rysuje aktualny stan graficzny gracza.
	*
	* @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
	*
	* Metoda wybiera bitmapy na podstawie aktualnego
	* kierunku ruchu oraz wyznacza fragment odpowiadajacy
	* biezacej klatce animacji.
	*
	* Wybrany fragment bitmapy jest rysowany za pomoca
	* metody DrawPart().
	*
	* Jesli indeks kierunku nie wskazuje dostepnej bitmapy,
	* gracz jest rysowany jako wypelniony prostokat.
	*/
	void Draw(class PrimitiveRenderer& renderer) const override;

	/**
	* @brief Aktualizuje stan gracza.
	*
	* @param deltaTime Czas, ktory uplynal od poprzedniej klatki.
	*
	* Metoda sprawdza stan klawiszy sterujacych,
	* aktualizuje polozenie i kierunek ruchu gracza
	* oraz zarzadza odtwarzaniem animacji.
	*
	* Podczas ruchu uruchamia animacje i aktualizuje
	* jej klatke. W przypadku braku ruchu zatrzymuje animacje.
	*/
	void Update(float deltaTime) override;

	/**
	* @brief Przesuwa gracza o podany wektor ruchu.
	*
	* @param tx Skladowa przesuniecia w osi X.
	* @param ty Skladowa przesuniecia w osi Y.
	*
	* Metoda mnozy podane wartosci przez predkosc gracza,
	* a nastepnie aktualizuje jego pozycje oraz polozenie
	* powiazanego obiektu graficznego.
	*/
	void Translate(float tx, float ty) override;

	/**
	* @brief Obraca gracza wzgledem poczatku ukladu wspolrzednych.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	*
	* Metoda obraca pozycje gracza oraz powiazany
	* obiekt graficzny wzgledem punktu (0, 0).
	*/
	void Rotate(float angle) override;

	/**
	* @brief Obraca gracza wzgledem wybranego punktu.
	*
	* @param angle Kat obrotu wyrazony w radianach.
	* @param origin Punkt, wzgledem ktorego wykonywany jest obrot.
	*
	* Metoda obraca pozycje gracza oraz powiazany
	* obiekt graficzny wzgledem wskazanego punktu.
	*/
	void Rotate(float angle, const Point2D& origin) override;

	/**
	* @brief Skaluje gracza wzgledem poczatku ukladu wspolrzednych.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	*
	* Metoda skaluje pozycje gracza oraz powiazany
	* obiekt graficzny wzgledem punktu (0, 0).
	*
	* Dodatkowo zmienia rozmiar wykorzystywany przy
	* rysowaniu zastepczym na podstawie wartosci
	* bezwzglednej wspolczynnika kx.
	*
	* @note Wspolczynnik ky nie wplywa na pole size.
	*/
	void Scale(float kx, float ky) override;

	/**
	* @brief Skaluje gracza wzgledem wybranego punktu.
	*
	* @param kx Wspolczynnik skalowania w osi X.
	* @param ky Wspolczynnik skalowania w osi Y.
	* @param origin Punkt, wzgledem ktorego wykonywane jest skalowanie.
	*
	* Metoda skaluje pozycje gracza oraz powiazany
	* obiekt graficzny wzgledem wskazanego punktu.
	*
	* Dodatkowo zmienia rozmiar wykorzystywany przy
	* rysowaniu zastepczym na podstawie wartosci
	* bezwzglednej wspolczynnika kx.
	*
	* @note Wspolczynnik ky nie wplywa na pole size.
	*/
	void Scale(float kx, float ky, const Point2D& origin) override;
};