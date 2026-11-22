/**
* @file PrimitiveRenderer.h
* @brief Definicja klasy odpowiedzialnej za renderowanie grafiki 2D.
*/

#pragma once
#include "raylib.h"
#include "Point2D.h"
#include "LineSegment.h"
#include <vector>

class BitmapHandler;
class RectangleObject;

/**
 * @class PrimitiveRenderer
 * @brief Klasa realizujaca programowe renderowanie grafiki dwuwymiarowej.
 *
 * Odpowiada za zarzadzanie buforem pikseli oraz
 * rysowanie podstawowych prymitywow graficznych,
 * takich jak odcinki, trojkaty, prostokaty,
 * okregi, elipsy i wielokaty.
 *
 * Udostepnia algorytmy wypelniania figur i obszarow,
 * a takze mechanizmy renderowania bitmap
 * z uwzglednieniem transformacji geometrycznych
 * i przezroczystosci.
 *
 * Umozliwia wyswietlanie zawartosci bufora w oknie aplikacji.
 */
class PrimitiveRenderer
{
private:
	int bufferWidth = 0;
	int bufferHeight = 0;
	mutable std::vector<Color> pixels;
	// Pomocnicze metody geometryczne do wykrywania przecięć odcinków
	/**
	* @brief Okresla orientacje trzech punktow.
	*
	* @param p Pierwszy punkt.
	* @param q Drugi punkt.
	* @param r Trzeci punkt.
	*
	* @return 0, jesli punkty sa wspolliniowe; 1, jesli sa ulozone zgodnie z ruchem wskazowek zegara; 2, jesli sa ulozone przeciwnie do ruchu wskazowek zegara.
	*
	* Metoda wyznacza orientacje uporzadkowanej
	* trojki punktow na podstawie ich wspolrzednych.
	*/
	int Orientation(const Point2D& p, const Point2D& q, const Point2D& r) const;

	/**
	* @brief Sprawdza, czy punkt nalezy do odcinka.
	*
	* @param p Pierwszy koniec odcinka.
	* @param q Sprawdzany punkt.
	* @param r Drugi koniec odcinka.
	*
	* @return true, jesli punkt q znajduje sie w granicach odcinka pr; false w przeciwnym przypadku.
	*
	* @note Metoda zaklada, ze punkty p, q i r sa wspolliniowe.
	*/
	bool OnSegment(const Point2D& p, const Point2D& q, const Point2D& r) const;

	/**
	* @brief Sprawdza, czy dwa odcinki sie przecinaja.
	*
	* @param s1 Pierwszy odcinek.
	* @param s2 Drugi odcinek.
	*
	* @return true, jesli odcinki maja co najmniej jeden punkt wspolny; false w przeciwnym przypadku.
	*
	* Metoda wykorzystuje orientacje punktow
	* oraz sprawdzanie przynaleznosci punktu
	* do odcinka.
	*
	* Uwzglednia przypadki przeciecia wlasciwego,
	* wspolliniowosci i stykania sie odcinkow.
	*/
	bool DoSegmentsIntersect(const LineSegment& s1, const LineSegment& s2) const;

public:
	/**
	* @brief Konstruktor klasy PrimitiveRenderer.
	*
	* Pobiera wymiary aktualnego okna aplikacji
	* i tworzy bufor pikseli o odpowiadajacej im wielkosci.
	*
	* Poczatkowo wszystkie piksele bufora maja kolor bialy.
	*
	* @note Konstruktor powinien zostac wywolany po zainicjalizowaniu okna graficznego.
	*/
	PrimitiveRenderer();


	/**
	* @brief Destruktor klasy PrimitiveRenderer.
	*
	* Konczy cykl zycia obiektu renderera.
	* Zasoby przechowywane w standardowych kontenerach
	* sa zwalniane automatycznie.
	*/
	~PrimitiveRenderer();

	/**
	* @brief Ustawia kolor pojedynczego piksela.
	*
	* @param point Punkt okreslajacy polozenie piksela.
	* @param color Nowy kolor piksela.
	*
	* Metoda wykorzystuje zaokraglone wspolrzedne
	* podanego punktu do zmiany koloru piksela w buforze.
	*
	* @note Piksele znajdujace sie poza granicami bufora sa pomijane.
	*/
	void PutPixel(const Point2D& point, Color color) const;

	/**
	* @brief Ustawia kolor piksela o podanych wspolrzednych.
	*
	* @param x Wspolrzedna X piksela.
	* @param y Wspolrzedna Y piksela.
	* @param color Nowy kolor piksela.
	*
	* Metoda zapisuje kolor we wskazanym miejscu bufora.
	*
	* @note Jesli wspolrzedne znajduja sie poza granicami bufora, operacja jest pomijana.
	*/
	void PutPixel(int x, int y, Color color) const;

	/**
	* @brief Pobiera kolor piksela z bufora.
	*
	* @param x Wspolrzedna X piksela.
	* @param y Wspolrzedna Y piksela.
	*
	* @return Kolor piksela znajdujacego sie pod wskazanymi wspolrzednymi.
	*
	* @note Jesli wspolrzedne znajduja sie poza granicami bufora, zwracany jest kolor BLANK.
	*/
	Color GetPixelColor(int x, int y) const;

	/**
	* @brief Czysci bufor pikseli.
	*
	* @param color Kolor, ktorym zostanie wypelniony bufor.
	*
	* Metoda ustawia wszystkie piksele bufora na wskazany kolor.
	*/
	void ClearBuffer(Color color) const;

	/**
	* @brief Wyswietla zawartosc bufora pikseli.
	*
	* Metoda przechodzi przez wszystkie piksele bufora
	* i rysuje je w oknie aplikacji za pomoca biblioteki
	* graficznej.
	*
	* @note Metoda nie zmienia zawartosci bufora.
	*/
	void RenderBuffer() const;

	/**
	* @brief Wypelnia spojny obszar o jednakowym kolorze.
	*
	* @param x Wspolrzedna X punktu poczatkowego.
	* @param y Wspolrzedna Y punktu poczatkowego.
	* @param color Nowy kolor wypelnienia.
	*
	* Metoda wykorzystuje iteracyjny algorytm Flood Fill
	* do zmiany koloru spojnego obszaru pikseli.
	*
	* Wypelnianie rozpoczyna sie od wskazanego punktu
	* i obejmuje sasiadujace piksele o takim samym
	* kolorze jak piksel poczatkowy.
	*
	* Do przeszukiwania obszaru wykorzystywany jest stos
	* oraz sasiedztwo czterokierunkowe.
	*
	* @note Jesli kolor poczatkowego piksela jest taki sam jak nowy kolor, metoda konczy dzialanie.
	*/
	void FloodFill(int x, int y, Color color) const;

	/**
	* @brief Wypelnia obszar ograniczony wskazanym kolorem.
	*
	* @param x Wspolrzedna X punktu poczatkowego.
	* @param y Wspolrzedna Y punktu poczatkowego.
	* @param fillColor Kolor wypelnienia.
	* @param borderColor Kolor wyznaczajacy granice obszaru.
	*
	* Metoda wykorzystuje iteracyjny algorytm Border Fill
	* do wypelniania obszaru ograniczonego pikselami
	* o okreslonym kolorze.
	*
	* Wypelnianie rozpoczyna sie od wskazanego punktu
	* i obejmuje sasiednie piksele, dopoki nie zostanie
	* napotkany kolor granicy lub kolor wypelnienia.
	*
	* Do przeszukiwania obszaru wykorzystywany jest stos
	* oraz sasiedztwo czterokierunkowe.
	*
	* @note Jesli kolor wypelnienia jest taki sam jak kolor granicy, metoda nie wykonuje operacji.
	*/
	void BorderFill(int x, int y, Color fillColor, Color borderColor) const;

	/**
	* @brief Rysuje odcinek za pomoca algorytmu DDA.
	*
	* @param p1 Punkt poczatkowy odcinka.
	* @param p2 Punkt koncowy odcinka.
	* @param color Kolor odcinka.
	*
	* Metoda wykorzystuje algorytm przyrostowy DDA,
	* obliczajac kolejne polozenia pikseli na podstawie
	* nachylenia odcinka.
	*
	* Kierunek iteracji jest dobierany na podstawie dominujacej osi odcinka.
	*/
	void DrawLine(const Point2D& p1, const Point2D& p2, Color color) const;

	/**
	* @brief Rysuje odcinek za pomoca algorytmu Bresenhama.
	*
	* @param p1 Punkt poczatkowy odcinka.
	* @param p2 Punkt koncowy odcinka.
	* @param color Kolor odcinka.
	*
	* Metoda wykorzystuje calkowitoliczbowy algorytm
	* Bresenhama do wyznaczania kolejnych pikseli odcinka.
	*
	* Obsluguje odcinki o dowolnym nachyleniu
	* oraz kierunku przebiegu.
	*/
	void DrawLineBresenham(const Point2D& p1, const Point2D& p2, Color color) const; 

	/**
	* @brief Rysuje lamana na podstawie wektora punktow.
	*
	* @param points Wektor kolejnych punktow lamanej.
	* @param color Kolor lamanej.
	* @param closed Okresla, czy lamana ma zostac zamknieta.
	*
	* Metoda laczy kolejne punkty odcinkami.
	* Jesli parametr closed ma wartosc true
	* i podano co najmniej trzy punkty,
	* laczy rowniez ostatni punkt z pierwszym.
	*
	* @note Dla mniej niz dwoch punktow metoda nie wykonuje rysowania.
	*/
	void DrawPolyline(const std::vector<Point2D>& points, Color color, bool closed = false) const; 

	/**
	* @brief Rysuje zbior odcinkow jako lamana.
	*
	* @param segments Wektor odcinkow do narysowania.
	* @param color Kolor rysowanych odcinkow.
	*
	* Metoda rysuje wszystkie odcinki znajdujace sie
	* w przekazanym wektorze.
	*
	* @note Metoda nie sprawdza ciaglosci ani polaczenia kolejnych odcinkow.
	*/
	void DrawPolyline(const std::vector<LineSegment>& segments, Color color) const;
	
	/**
	* @brief Rysuje kontur trojkata.
	*
	* @param p1 Pierwszy wierzcholek trojkata.
	* @param p2 Drugi wierzcholek trojkata.
	* @param p3 Trzeci wierzcholek trojkata.
	* @param color Kolor konturu.
	*
	* Metoda rysuje trzy odcinki laczace wszystkie wierzcholki trojkata.
	*/
	void DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;

	/**
	* @brief Rysuje kontur prostokata.
	*
	* @param p1 Punkt odniesienia prostokata.
	* @param width Szerokosc prostokata.
	* @param height Wysokosc prostokata.
	* @param color Kolor konturu.
	*
	* Metoda wyznacza cztery wierzcholki prostokata
	* o bokach rownoleglych do osi ukladu wspolrzednych
	* i laczy je odcinkami.
	*
	* Ujemne wartosci szerokosci i wysokosci
	* okreslaja rozciagniecie prostokata
	* w przeciwnym kierunku odpowiedniej osi.
	*/
	void DrawRectangle(const Point2D& p1, int width, int height, Color color) const;

	/**
	* @brief Rysuje kontur okregu.
	*
	* @param center Srodek okregu.
	* @param radius Promien okregu.
	* @param color Kolor konturu.
	*
	* Metoda wyznacza punkty okregu na podstawie
	* funkcji trygonometrycznych i wykorzystuje
	* osmiokrotna symetrie do rysowania konturu.
	*
	* @note Dla promienia mniejszego lub rownego zero metoda nie wykonuje rysowania.
	*/
	void DrawCircle(const Point2D& center, int radius, Color color) const;

	/**
	* @brief Rysuje kontur elipsy.
	*
	* @param center Srodek elipsy.
	* @param radiusX Promien elipsy w osi X.
	* @param radiusY Promien elipsy w osi Y.
	* @param color Kolor konturu.
	*
	* Metoda wyznacza punkty konturu elipsy
	* na podstawie funkcji trygonometrycznych
	* i wykorzystuje symetrie wzgledem obu osi.
	*
	* @note Dla promieni mniejszych lub rownych zero metoda nie wykonuje rysowania.
	*/
	void DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;

	// Rysowanie wielokąta (łamanej zwyczajnej zamkniętej) - przerywa, jeśli krawędzie się przecinają

	/**
	* @brief Rysuje kontur wielokata na podstawie wierzcholkow.
	*
	* @param points Wektor wierzcholkow wielokata.
	* @param color Kolor konturu.
	*
	* Metoda tworzy odcinki laczace kolejne wierzcholki,
	* lacznie z ostatnim i pierwszym.
	*
	* Nastepnie przekazuje utworzone krawedzie
	* do metody sprawdzajacej poprawnosc wielokata
	* i wykonujacej jego rysowanie.
	*
	* @note Wielokat musi posiadac co najmniej trzy wierzcholki.
	*/
	void DrawPolygon(const std::vector<Point2D>& points, Color color) const;

	/**
	* @brief Rysuje kontur wielokata na podstawie odcinkow.
	*
	* @param segments Wektor krawedzi wielokata.
	* @param color Kolor konturu.
	*
	* Metoda sprawdza, czy przekazane odcinki
	* tworza ciagly i zamkniety kontur.
	*
	* Nastepnie weryfikuje, czy niesasiadujace
	* krawedzie nie przecinaja sie.
	*
	* Jesli kontur jest poprawny, rysuje
	* wszystkie jego krawedzie.
	*
	* @note Niepoprawne wielokaty nie sa rysowane.
	*/
	void DrawPolygon(const std::vector<LineSegment>& segments, Color color) const;

	/**
	* @brief Rysuje wypelniony trojkat.
	*
	* @param p1 Pierwszy wierzcholek trojkata.
	* @param p2 Drugi wierzcholek trojkata.
	* @param p3 Trzeci wierzcholek trojkata.
	* @param color Kolor wypelnienia.
	*
	* Metoda wyznacza prostokat ograniczajacy trojkat,
	* a nastepnie sprawdza kolejne piksele
	* pod katem przynaleznosci do jego wnetrza.
	*
	* Wykorzystuje funkcje krawedziowe do okreslenia,
	* czy dany piksel znajduje sie wewnatrz trojkata
	* lub na jego krawedzi.
	*/
	void DrawFilledTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;

	/**
	* @brief Rysuje wypelniony prostokat.
	*
	* @param p1 Punkt odniesienia prostokata.
	* @param width Szerokosc prostokata.
	* @param height Wysokosc prostokata.
	* @param color Kolor wypelnienia.
	*
	* Metoda wypelnia piksele prostokatnego obszaru
	* o bokach rownoleglych do osi ukladu wspolrzednych.
	*
	* Ujemne wartosci szerokosci i wysokosci
	* okreslaja kierunek rozciagniecia prostokata.
	*/
	void DrawFilledRectangle(const Point2D& p1, int width, int height, Color color) const;

	/**
	* @brief Rysuje wypelniony okrag.
	*
	* @param center Srodek okregu.
	* @param radius Promien okregu.
	* @param color Kolor wypelnienia.
	*
	* Metoda wyznacza poziome odcinki nalezace
	* do wnetrza okregu na podstawie jego rownania.
	*
	* Nastepnie wypelnia wszystkie piksele
	* znajdujace sie na wyznaczonych odcinkach.
	*
	* @note Dla promienia mniejszego lub rownego zero metoda nie wykonuje rysowania.
	*/
	void DrawFilledCircle(const Point2D& center, int radius, Color color) const;

	/**
	* @brief Rysuje wypelniona elipse.
	*
	* @param center Srodek elipsy.
	* @param radiusX Promien elipsy w osi X.
	* @param radiusY Promien elipsy w osi Y.
	* @param color Kolor wypelnienia.
	*
	* Metoda wyznacza poziome odcinki nalezace
	* do wnetrza elipsy na podstawie jej rownania.
	*
	* Nastepnie wypelnia piksele znajdujace sie
	* pomiedzy wyznaczonymi granicami.
	*
	* @note Dla promieni mniejszych lub rownych zero metoda nie wykonuje rysowania.
	*/
	void DrawFilledEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;

	/**
	* @brief Rysuje wypelniony wielokat.
	*
	* @param points Wektor wierzcholkow wielokata.
	* @param color Kolor wypelnienia i konturu.
	*
	* Metoda sprawdza, czy wielokat nie posiada
	* przecinajacych sie niesasiadujacych krawedzi.
	*
	* Nastepnie wykorzystuje algorytm scanline
	* z regula parzystosci do wypelnienia jego wnetrza.
	*
	* Po zakonczeniu wypelniania rysuje kontur wielokata.
	*
	* @note Wielokat musi posiadac co najmniej trzy wierzcholki.
	*
	* @note W przypadku wykrycia przecinajacych sie krawedzi metoda przerywa rysowanie.
	*/
	void DrawFilledPolygon(const std::vector<Point2D>& points, Color color) const;

	/**
	* @brief Rysuje wybrany fragment bitmapy po transformacji geometrycznej.
	*
	* @param bitmap Bitmapa zawierajaca dane obrazu.
	* @param source Prostokat okreslajacy fragment bitmapy do narysowania.
	* @param topLeft Przeksztalcony lewy gorny wierzcholek bitmapy.
	* @param topRight Przeksztalcony prawy gorny wierzcholek bitmapy.
	* @param bottomLeft Przeksztalcony lewy dolny wierzcholek bitmapy.
	*
	* Metoda rysuje wskazany fragment bitmapy
	* w buforze pikseli z uwzglednieniem jego
	* polozenia, obrotu i skalowania.
	*
	* Na podstawie trzech przekazanych wierzcholkow
	* wyznacza obszar docelowy oraz transformacje
	* odwrotna, pozwalajaca przypisac piksele
	* bitmapy do odpowiednich pikseli bufora.
	*
	* Podczas renderowania wykorzystuje probkowanie
	* najblizszego sasiada oraz obsluguje przezroczystosc
	* na podstawie kanalu alfa.
	*
	* @note Metoda nie wykonuje rysowania, jesli bitmapa jest niepoprawna, obszar zrodlowy ma niepoprawne wymiary lub transformacja jest osobliwa.
	*/
	void DrawBitmap(const BitmapHandler& bitmap, const RectangleObject& source,	const Point2D& topLeft,	const Point2D& topRight, const Point2D& bottomLeft) const;
};