/**
* @file BitmapHandler.h
* @brief Obsluga bitmap
* 
* Plik zawiera klase sluzaca do obslugi bitmap (tworzenie, usuwanie, ladowanie z pliku, zapis do pliku itp.)
*/

#pragma once
#include "raylib.h"

/**
* @class BitmapHandler
* 
* @brief Klasa zawierajaca metody sluzace do obslugi bitmap
*/
class BitmapHandler
{
private:
    Image bitmap;

public:

    /**
    * @brief Domyslny konstruktor tworzacy pusty obiekt
    * 
    * Inicjalizuje bitmape bez alokowania pamieci
    */
    BitmapHandler();

    /**
    * @brief Destruktor usuwajacy obiekt i czyszczacy zaalokowana na niego pamiec
    */
    ~BitmapHandler();

    /**
    * @brief Konstruktor kopiujacy tworzacy kopie na podstawie innej bitmapy
    * 
    * @param other Inny obiekt typu BitmapHandler, ktorego kopie chcemy utworzyc
    */
    BitmapHandler(const BitmapHandler& other);

    /**
    * @brief Nadpisanie operatora przypisania w celu ulatwienia kopiowania bitmap
    * 
    * @param other Obiekt typu BitmapHandler ktory chcemy skopiowac
    * 
    * @return Referencja do biezacego obiektu BitmapHandler
    * 
    * Funkcja umozliwia przypisanie zawartosci jednej bitmapy do drugiej, juz istniejacej bitmapy, np. bitmap1 = bitmap2.
    */
    BitmapHandler& operator=(const BitmapHandler& other);

    /**
    * @brief Tworzenie bitmapy o podanych wymiarach i kolorze
    * 
    * @param width Szerokosc (w pikselach) bitmapy ktora chcemy stworzyc
    * @param height Wysokosc (w pikselach) bitmapy ktora chcemy stworzyc
    * @param color Kolor bitmapy ktora chcemy stworzyc (domyslnie WHITE)
    * 
    * @return True, jesli bitmapa zostanie pomyslnie utworzona, False w przeciwnym wypadku
    * 
    */
    bool create(int width, int height, Color color = WHITE);

    /**
    * @brief Usuniecie bitmapy
    * 
    * Funkcja zwalnia pamiec zajmowana przez bitmape i przywraca jej pusty stan
    */
    void remove();

    /**
    * @brief Ladowanie bitmapy z pliku
    * 
    * @param filename Sciezka do pliku z ktorego chcemy zaladowac bitmape
    * 
    * @return True jesli bitmape uda sie zaladowac, False jesli nie
    * 
    * Funkcja wczytuje bitmape z danego pliku, po czym zapisuje ja w biezacym obiekcie
    */
    bool load(const char* filename);

    /**
    * @brief Zapisanie bitmapy do pliku
    * 
    * @param filename Nazwa pliku pod jaka chcemy zapisac obecna bitmape
    * @return True jesli zapisanie sie uda, False jesli nie
    */
    bool save(const char* filename) const;

    /**
    * @brief Skopiowanie innej bitmapy do istniejacego obiektu
    * @param other Referencja do bitmapy ktora chcemy skopiowac
    * 
    * Metoda kopiuje bitmape i przypisuje ja do obecnego obiektu. W odroznieniu od konstruktora kopiujacego,
    * metoda nie tworzy nowego obiektu tylko modyfikuje juz istniejacy.
    */
    void copy(const BitmapHandler& other);

    /**
    * @brief Odczyt szerokosci bitmapy
    * @return Szerokosc bitmapy
    * 
    * Metoda zwraca szerokosc bitmapy w pikselach
    */
    int getWidth() const;

    /**
    * @brief Odczyt wysokosci bitmapy
    * @return Wysokosc bitmapy
    * 
    * Metoda zwraca wysokosc bitmapy w pikselach
    */
    int getHeight() const;

    /**
    * @brief Odczyt koloru na podanych wspolrzednych
    * @param x Wspolrzedna x wewnatrz bitmapy
    * @param y Wspolrzedna y wewnatrz bitmapy
    * @return Kolor piksela znajdujacego sie na danych wspolrzednych
    * 
    * Metoda zwraca jakiego koloru jest piksel w podanym miejscu bitmapy,
    * JESLI wspolrzedne znajduja sie w jej obrebie. W przeciwnym wypadku zwraca BLANK
    * 
    */
    Color getPixel(int x, int y) const;

    /**
    * @brief Sprawdzenie poprawnosci bitmapy
    * 
    * @return True jesli bitmapa jest poprawna, False w przeciwnym przypadku
    * 
    * Metoda sprawdza poprawnosc bitmapy poprzez sprawdzenie czy jej rozmiary sa wieksze od zera, oraz czy
    * posiada wskaznik do danych obrazu
    */
    bool isValid() const;

    /**
    * @brief Utworzenie tekstury do wyswietlenia
    * 
    * @return Tekstura gotowa do wyswietlenia (lub pusta struktura jesli bitmapa jest niepoprawna)
    * 
    * Metoda bierze bitmape przechowywana w obiekcie i konwertuje ja na teksture,
    * ktora mozna wyswietlic w oknie
    */
    Texture2D createTexture() const;

};