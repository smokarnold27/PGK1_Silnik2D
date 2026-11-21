/**
* @file Engine.h
* @brief Glowny plik silnika, zawiera definicje klasy Engine ktora laczy wszystko w calosc
*/

#pragma once
#include "raylib.h"
#include "ShapeObject.h"
#include "BitmapObject.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

/**
 * @class Engine
 * @brief Glowna klasa odpowiedzialna za zarzadzanie silnikiem gry 2D.
 *
 * Klasa odpowiada za inicjalizacje srodowiska graficznego,
 * konfiguracje okna aplikacji, zarzadzanie obiektami,
 * obsluge glownej petli silnika oraz zamykanie aplikacji.
 *
 * Wykorzystuje klase PrimitiveRenderer do rysowania
 * obiektow w buforze pikseli i wyswietlania jego
 * zawartosci w oknie aplikacji.
 *
 * Klasa wykorzystuje wzorzec projektowy Singleton,
 * zapewniajac dostep do jednej instancji silnika.
 */
class Engine
{
private:
	/**
	* @brief Konstruktor klasy Engine.
	*
	* Inicjalizuje podstawowe ustawienia silnika,
	* takie jak wymiary okna, tryb pelnoekranowy,
	* docelowa liczba klatek na sekunde oraz stan pracy.
	*
	* Domyslnie ustawia rozdzielczosc 800x600,
	* tryb okienkowy oraz limit 60 FPS.
	* 
	* Konstruktor jest prywatny, aby uniemozliwic tworzenie obiektow klasy Engine z zewnatrz
	*/
	Engine();

	/**
	* @brief Destruktor klasy Engine.
	*
	* Wywoluje metode Shutdown() w celu zakonczenia
	* pracy silnika i zamkniecia srodowiska graficznego,
	* jesli silnik nadal jest uruchomiony.
	* 
	* Destruktor jest prywatny, aby nie mozna bylo go wywolac z zewnatrz
	*/
	~Engine();

	bool is_running;
	int screen_width;
	int screen_height;
	bool is_fullscreen;
	int target_fps;

	vector<unique_ptr<ShapeObject>> objects;
	vector<unique_ptr<BitmapObject>> bitmap_objects;

public:
	/**
	* @brief Usuniety konstruktor kopiujacy klasy Engine.
	*
	* Uniemozliwia tworzenie kopii obiektu Engine,
	* zapewniajac zgodnosc ze wzorcem Singleton.
	*/
	Engine(const Engine&) = delete;

	/**
	* @brief Usuniety operator przypisania kopiujacego klasy Engine.
	*
	* Uniemozliwia przypisywanie zawartosci jednego obiektu
	* Engine do drugiego, zapobiegajac kopiowaniu instancji silnika.
	*
	* Operator zostal usuniety w celu zachowania
	* zalozen wzorca Singleton.
	*/
	Engine& operator=(const Engine&) = delete;

	/**
	* @brief Zwraca jedyna instancje klasy Engine.
	*
	* @return Referencja do instancji silnika.
	*
	* Metoda realizuje wzorzec projektowy Singleton.
	* Przy pierwszym wywolaniu tworzy statyczna instancje
	* klasy Engine, a przy kolejnych zwraca referencje
	* do tego samego obiektu.
	*/
	static Engine& GetInstance();

	/**
	 * @brief Inicjalizuje silnik gry i srodowisko graficzne.
	 *
	 * @param width Szerokosc okna aplikacji w pikselach.
	 * @param height Wysokosc okna aplikacji w pikselach.
	 * @param fullscreen Okresla, czy aplikacja ma dzialac w trybie pelnoekranowym.
	 * @param fps Docelowa liczba klatek na sekunde.
	 *
	 * @return true, jesli inicjalizacja zakonczyla sie powodzeniem,
	 * false w przypadku niepowodzenia.
	 *
	 * Metoda zapisuje ustawienia silnika, konfiguruje
	 * parametry okna, inicjalizuje srodowisko graficzne
	 * i ustawia docelowa liczbe klatek na sekunde.
	 *
	 * Po pomyslnej inicjalizacji ustawia stan silnika jako uruchomiony.
	 */
	bool Init(int width, int height, bool fullscreen, int fps);

	/**
	* @brief Uruchamia glowna petle silnika.
	*
	* Metoda tworzy renderer, przygotowuje bufor pikseli
	* oraz wykonuje glowna petle aplikacji.
	*
	* W kazdej iteracji obsluguje zdarzenia wejscia,
	* aktualizuje stan obiektow, wykonuje operacje
	* rysowania i wyswietla zawartosc bufora w oknie.
	*
	* Petla dziala do momentu zakonczenia pracy silnika
	* lub otrzymania zadania zamkniecia okna.
	*
	* @note Metode nalezy wywolac po pomyslnej
	* inicjalizacji silnika za pomoca Init().
	*/
	void Run();

	/**
	* @brief Konczy prace silnika.
	*
	* Metoda zamyka okno aplikacji i ustawia stan
	* silnika jako nieaktywny, jesli silnik
	* jest aktualnie uruchomiony.
	*/
	void Shutdown();

	/**
	* @brief Zwraca szerokosc okna
	* @return Szerokosc okna w pikselach
	*/
	int GetScreenWidth() const { return screen_width; }

	/**
	* @brief Zwraca wysokosc okna
	* @return Wysokosc okna w pikselach
	*/
	int GetScreenHeight() const { return screen_height; }
};