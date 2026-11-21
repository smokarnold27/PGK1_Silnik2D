/**
* @file SpriteObject.h
* @brief Definicja klasy obslugujacej animowane sprite'y 2D.
*/

#pragma once
#include "BitmapObject.h"
#include "AnimatedObject.h"

/**
* @class SpriteObject
* @brief Klasa reprezentujaca obiekt graficzny z animacja klatkowa.
*
* Rozszerza funkcjonalnosc klasy BitmapObject
* o mozliwosc odtwarzania animacji na podstawie
* arkuszy sprite'ow.
*
* Umozliwia wczytywanie bitmap zawierajacych
* kolejne klatki animacji, sterowanie odtwarzaniem
* oraz okreslanie liczby klatek na sekunde.
*
* Kazdy arkusz sprite'ow jest dzielony na klatki
* o jednakowej szerokosci, ulozone poziomo.
*/
class SpriteObject : public BitmapObject, public AnimatedObject
{
protected:
    int frameCount;
    int currentFrame = 0;

    float frameDuration;
    float elapsedTime = 0.0f;

    bool playing = true;

public:

    /**
    * @brief Konstruktor klasy SpriteObject.
    *
    * @param frames Liczba klatek animacji w kazdym arkuszu sprite'ow.
    * @param fps Liczba klatek animacji wyswietlanych na sekunde.
    *
    * Inicjalizuje liczbe klatek animacji oraz
    * czas wyswietlania pojedynczej klatki.
    *
    * Jesli liczba klatek jest mniejsza lub rowna zero,
    * zostaje ustawiona na 1.
    *
    * @note Niepoprawna wartosc fps powoduje pozostawienie domyslnego czasu klatki wynoszacego 0.1 sekundy.
    */
    SpriteObject(int frames, float fps = 10.0f);

    /**
    * @brief Dodaje arkusz sprite'ow do obiektu.
    *
    * @param filename Sciezka do pliku zawierajacego arkusz sprite'ow.
    * @param offset Przesuniecie bitmapy wzgledem lokalnego ukladu obiektu.
    *
    * @return true, jesli bitmapa zostala poprawnie wczytana i dodana; false w przypadku niepowodzenia.
    *
    * Metoda wczytuje bitmape z pliku i sprawdza,
    * czy jej szerokosc jest podzielna przez
    * liczbe klatek animacji.
    *
    * Jesli warunki sa spelnione, zapisuje bitmape
    * wraz z jej przesunieciem w kolekcji obiektu.
    *
    * @note Wszystkie klatki arkusza musza miec jednakowa szerokosc i byc ulozone poziomo.
    */
    bool AddBitmap(const char* filename, const Point2D& offset = Point2D()) override;


    /**
    * @brief Aktualizuje biezaca klatke animacji.
    *
    * Metoda aktualizuje czas odtwarzania animacji
    * na podstawie czasu trwania ostatniej klatki aplikacji.
    *
    * Jesli zgromadzony czas przekroczy czas trwania
    * pojedynczej klatki animacji, aktualizuje
    * indeks aktualnie wyswietlanej klatki.
    *
    * Po osiagnieciu ostatniej klatki animacja
    * rozpoczyna sie ponownie od pierwszej.
    *
    * @note Metoda nie wykonuje aktualizacji, jesli animacja nie jest odtwarzana.
    *
    * @note Czas aktualizacji pobierany jest za pomoca funkcji GetFrameTime().
    */
    void animate() override;

    /**
    * @brief Rysuje aktualna klatke animacji.
    *
    * @param renderer Referencja do renderera odpowiedzialnego za rysowanie.
    *
    * Metoda przechodzi przez wszystkie arkusze sprite'ow
    * przypisane do obiektu.
    *
    * Dla kazdego arkusza wyznacza prostokat zrodlowy
    * odpowiadajacy aktualnej klatce animacji,
    * a nastepnie rysuje go za pomoca metody DrawPart().
    *
    * @note Wszystkie arkusze wykorzystuja ten sam indeks aktualnej klatki animacji.
    */
    void Draw(PrimitiveRenderer& renderer) const override;

    /**
    * @brief Rozpoczyna lub wznawia odtwarzanie animacji.
    *
    * Metoda ustawia stan animacji na aktywny.
    *
    * Nie zmienia aktualnej klatki ani zgromadzonego
    * czasu animacji.
    */
    void Play();

    /**
    * @brief Wstrzymuje odtwarzanie animacji.
    *
    * Metoda zatrzymuje aktualizacje klatek animacji,
    * zachowujac biezacy indeks klatki
    * oraz zgromadzony czas.
    *
    * Animacja moze zostac wznowiona metoda Play().
    */
    void Pause();

    /**
    * @brief Zatrzymuje i resetuje animacje.
    *
    * Metoda wylacza odtwarzanie animacji,
    * ustawia indeks aktualnej klatki na zero
    * oraz zeruje zgromadzony czas.
    *
    * Ponowne wywolanie Play() rozpocznie
    * animacje od pierwszej klatki.
    */
    void Stop();

    /**
    * @brief Ustawia predkosc odtwarzania animacji.
    *
    * @param fps Liczba klatek animacji na sekunde.
    *
    * Metoda oblicza czas wyswietlania pojedynczej
    * klatki jako odwrotnosc podanej wartosci fps.
    *
    * Dla poprawnej wartosci zeruje rowniez
    * zgromadzony czas animacji.
    *
    * @note Wartosc fps musi byc dodatnia i skonczona. Niepoprawne wartosci sa ignorowane.
    */
    void SetFPS(float fps);

    /**
    * @brief Zwraca indeks aktualnej klatki animacji.
    *
    * @return Indeks aktualnie wyswietlanej klatki.
    *
    * Indeksowanie klatek rozpoczyna sie od zera.
    */
    int GetCurrentFrame() const;
};