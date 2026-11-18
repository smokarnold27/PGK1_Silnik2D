#pragma once
#include "raylib.h"
#include "ShapeObject.h"
#include "BitmapObject.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class Engine
{
private:
	// Konstruktor prywatny, aby uniemożliwić tworzenie obiektów klasy Engine z zewnątrz
	Engine();
	~Engine();

	bool is_running;
	int screen_width;
	int screen_height;
	bool is_fullscreen;
	int target_fps;

	vector<unique_ptr<ShapeObject>> objects;
	vector<unique_ptr<BitmapObject>> bitmap_objects;

public:
	// Usunięcie konstruktora kopiującego i operatora przypisania, aby uniemożliwić tworzenie kopii obiektu Engine (wzorzec singleton)
	Engine(const Engine&) = delete; // usunięcie konstruktora kopiującego
	Engine& operator=(const Engine&) = delete; // usunięcie operatora przypisania

	static Engine& GetInstance(); // metoda statyczna zwracająca referencję do jedynego obiektu klasy Engine

	bool Init(int width, int height, bool fullscreen, int fps);
	void Run();
	void Shutdown();

	int GetScreenWidth() const { return screen_width; }
	int GetScreenHeight() const { return screen_height; }
};