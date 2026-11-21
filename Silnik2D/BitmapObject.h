/**
* @file BitmapObject.h
* 
* @brief Definicja klasy sluzacej do wyswietlania i transformowania bitmap
*/

#pragma once

#include "DrawableObject.h"
#include "TransformableObject.h"
#include "BitmapHandler.h"
#include "Point2D.h"
#include "RectangleObject.h"
#include <vector>

/**
* @class BitmapObject
* @brief Klasa dzieki ktorej mozna wyswietlac bitmapy w oknie
* 
* Klasa dziedziczy po DrawableObject i po TransformableObject, aby mozna bylo wyswietlic mape na ekranie, i ja transformowac
*/
class BitmapObject : public DrawableObject, public TransformableObject
{
protected:
    struct BitmapPart
    {
        BitmapHandler bitmap;
        Point2D offset;
    };

    std::vector<BitmapPart> bitmaps;

    Point2D position{ 0.0f, 0.0f };
    Point2D axisX{ 1.0f, 0.0f };
    Point2D axisY{ 0.0f, 1.0f };

    /**
    * @brief Przeksztalca punkt z lokalnego ukladu wspolrzednych bitmapy.
    *
    * @param point Punkt, ktorego wspolrzedne chcemy przeksztalcic.
    * @return Punkt o wspolrzednych po wykonaniu transformacji.
    *
    * Metoda oblicza nowe wspolrzedne punktu na podstawie pozycji bitmapy oraz kierunkow i dlugosci jej osi.
    * Uwzglednia wczesniej wykonane przesuniecia, obroty i skalowania obiektu.
    */
    Point2D TransformPoint(const Point2D& point) const;

    /**
    * @brief Rysuje pojedyncza bitmape nalezaca do obiektu.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    * @param part Czesc obiektu zawierajaca bitmape i jej lokalne przesuniecie.
    * @param source Prostokat okreslajacy fragment bitmapy przeznaczony do narysowania.
    *
    * Metoda wyznacza trzy narozniki obszaru rysowania na podstawie przesuniecia bitmapy i wymiarow wybranego fragmentu.
    * Nastepnie przeksztalca ich wspolrzedne zgodnie z aktualna transformacja obiektu i przekazuje dane do renderera.
    */
    void DrawPart(PrimitiveRenderer& renderer, const BitmapPart& part, const RectangleObject& source) const;

public:
    /**
    * @brief Konstruktor domyslny
    */
    BitmapObject() = default;
    virtual ~BitmapObject() = default;


    /**
    * @brief Dodaje nowa bitmape do obiektu.
    *
    * @param filename Sciezka do pliku zawierajacego bitmape.
    * @param offset Punkt okreslajacy lokalne przesuniecie bitmapy wzgledem poczatku ukladu wspolrzednych obiektu.
    *
    * @return true, jesli bitmape udalo sie wczytac i dodac, false w przeciwnym przypadku.
    *
    * Metoda wczytuje bitmape z podanego pliku, przypisuje jej lokalne przesuniecie,
    * a nastepnie dodaje ja do listy bitmap nalezacych do obiektu.
    */
    virtual bool AddBitmap(const char* filename, const Point2D& offset = Point2D());

    /**
    * @brief Usuwa bitmape o podanym indeksie.
    *
    * @param index Indeks bitmapy, ktora chcemy usunac.
    *
    * Metoda usuwa wskazana bitmape z listy bitmap obiektu. Jesli podany indeks jest niepoprawny, 
    * nie wykonuje zadnej operacji.
    */
    void RemoveBitmap(int index);

    /**
    * @brief Usuwa wszystkie bitmapy nalezace do obiektu.
    *
    * Metoda czysci liste bitmap przechowywanych w obiekcie,
    * zwalniajac zasoby nalezace do usuwanych elementow.
    */
    void ClearBitmaps();

    /**
    * @brief Zwraca liczbe bitmap nalezacych do obiektu.
    *
    * @return Liczba bitmap aktualnie przechowywanych w obiekcie.
    */
    int GetBitmapCount() const;

    /**
    * @brief Rysuje wszystkie bitmapy nalezace do obiektu.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    *
    * Metoda przechodzi przez wszystkie bitmapy przechowywane
    * w obiekcie i rysuje kazda z nich z uwzglednieniem
    * jej lokalnego przesuniecia oraz transformacji calego obiektu.
    */
    void Draw(PrimitiveRenderer& renderer) const override;

    /**
    * @brief Przesuwa obiekt o podany wektor.
    *
    * @param tx Przesuniecie w osi X.
    * @param ty Przesuniecie w osi Y.
    *
    * Metoda przesuwa poczatek ukladu wspolrzednych obiektu
    * oraz punkty okreslajace kierunki jego osi.
    * Przesuniecie dotyczy wszystkich bitmap nalezacych do obiektu.
    */
    void Translate(float tx, float ty) override;

    /**
    * @brief Obraca obiekt wzgledem poczatku ukladu wspolrzednych.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    *
    * Metoda obraca pozycje obiektu oraz punkty okreslajace
    * jego osie wzgledem punktu (0, 0).
    * Obrot dotyczy wszystkich bitmap nalezacych do obiektu.
    */
    void Rotate(float angle) override;

    /**
    * @brief Obraca obiekt wzgledem wybranego punktu.
    *
    * @param angle Kat obrotu wyrazony w radianach.
    * @param origin Punkt, wzgledem ktorego wykonujemy obrot.
    *
    * Metoda obraca pozycje obiektu oraz punkty okreslajace
    * jego osie wzgledem wskazanego punktu.
    * Obrot dotyczy wszystkich bitmap nalezacych do obiektu.
    */
    void Rotate(float angle, const Point2D& origin) override;

    /**
    * @brief Skaluje obiekt wzgledem poczatku ukladu wspolrzednych.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    *
    * Metoda skaluje pozycje obiektu oraz punkty okreslajace
    * jego osie wzgledem punktu (0, 0).
    * Skalowanie dotyczy wszystkich bitmap nalezacych do obiektu.
    */
    void Scale(float kx, float ky) override;

    /**
    * @brief Skaluje obiekt wzgledem wybranego punktu.
    *
    * @param kx Wspolczynnik skalowania w osi X.
    * @param ky Wspolczynnik skalowania w osi Y.
    * @param origin Punkt, wzgledem ktorego wykonujemy skalowanie.
    *
    * Metoda skaluje pozycje obiektu oraz punkty okreslajace
    * jego osie wzgledem wskazanego punktu.
    * Skalowanie dotyczy wszystkich bitmap nalezacych do obiektu.
    */
    void Scale(float kx, float ky, const Point2D& origin) override;
};