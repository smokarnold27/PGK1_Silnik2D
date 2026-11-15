#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "TriangleObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "EllipseObject.h"
#include "PolygonObject.h"

using namespace std;

Engine::Engine() : is_running(false), screen_width(800), screen_height(600), is_fullscreen(false), target_fps(60) {}

Engine::~Engine()
{
	Shutdown();
}

Engine& Engine::GetInstance()
{
	static Engine instance;
	return instance;
}

bool Engine::Init(int width, int height, bool fullscreen, int fps)
{
	screen_width = width;
	screen_height = height;
	is_fullscreen = fullscreen;
	target_fps = fps;

	if (is_fullscreen) {
		SetConfigFlags(FLAG_FULLSCREEN_MODE);
	}
	else {
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	}

	InitWindow(screen_width, screen_height, "Silnik 2D");
	if (!IsWindowReady()) {
		cerr << "Błąd! Nie udało się zainicjalizować okna biblioteki graficznej!" << endl;
		return false;
	}
	SetTargetFPS(target_fps);
	is_running = true;

	objects.clear(); // Czyszczenie listy obiektów przy inicjalizacji silnika

	// Punkt
	objects.push_back(std::make_unique<Point2D>(400.0f, 300.0f, PURPLE));

	// Odcinek (Bresenham)
	objects.push_back(std::make_unique<LineSegment>(Point2D(100, 400), Point2D(500, 100), RED, LineAlgorithm::Bresenham));

	// Odcinek (DDA)
	objects.push_back(std::make_unique<LineSegment>(Point2D(50, 100), Point2D(300, 150), GREEN, LineAlgorithm::DDA));

	// Trójkąt (konturowy)
	objects.push_back(std::make_unique<TriangleObject>(Point2D(150, 200), Point2D(350, 350), Point2D(200, 380), BLUE, false));

	// Trójkąt (wypełniony)
	objects.push_back(std::make_unique<TriangleObject>(Point2D(450, 200), Point2D(600, 300), Point2D(500, 350), SKYBLUE, true));

	// Prostokąt (konturowy)
	objects.push_back(std::make_unique<RectangleObject>(Point2D(500, 400), 150.0f, 90.0f, BLACK, false));

	// Prostokąt (wypełniony)
	objects.push_back(std::make_unique<RectangleObject>(Point2D(50, 450), 120.0f, 80.0f, ORANGE, true));

	// Okrąg (konturowy)
	objects.push_back(std::make_unique<CircleObject>(Point2D(200, 200), 50, PINK, false));

	// Okrąg (wypełniony)
	objects.push_back(std::make_unique<CircleObject>(Point2D(450, 490), 45, MAROON, true));

	// Elipsa (konturowa)
	objects.push_back(std::make_unique<EllipseObject>(Point2D(400, 200), 70, 35, BLACK, false));

	// Elipsa (wypełniona)
	objects.push_back(std::make_unique<EllipseObject>(Point2D(630, 490), 80, 40, MAGENTA, true));

	// Wielokąt (konturowy)
	std::vector<Point2D> polyPoints = {
		Point2D(520, 80),
		Point2D(680, 60),
		Point2D(720, 180),
		Point2D(610, 140),
		Point2D(540, 200)
	};
	objects.push_back(std::make_unique<PolygonObject>(polyPoints, DARKGREEN, false, true));

	// Wielokąt (wypełniony)
	std::vector<Point2D> filledPolyPoints = {
		Point2D(60, 260),
		Point2D(160, 240),
		Point2D(130, 310),
		Point2D(170, 370),
		Point2D(50, 350)
	};
	objects.push_back(std::make_unique<PolygonObject>(filledPolyPoints, LIME, true, true));

	return true;
}

void Engine::Run() 
{
	PrimitiveRenderer renderer;
	renderer.ClearBuffer(WHITE);
	// 2. Polimorficzne rysowanie wszystkich obiektów z listy do bufora
	for (const auto& obj : objects) {
		obj->Draw(renderer);
	}

	while (is_running && !WindowShouldClose())
	{
		/*if (IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
            cout << "Zmieniono rozdzielczość okna na: " << screen_width << "x" << screen_height << endl;
        }*/
		float delta_time = GetFrameTime();
		if (IsKeyPressed(KEY_ESCAPE)) {
			is_running = false;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mouse = GetMousePosition();
			renderer.FloodFill(
				static_cast<int>(mouse.x),
				static_cast<int>(mouse.y),
				YELLOW
			);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 mouse = GetMousePosition();
			renderer.BorderFill(
				static_cast<int>(mouse.x),
				static_cast<int>(mouse.y),
				SKYBLUE, // kolor wypełnienia
				BLACK    // kolor konturu (granicy)
			);
		}

		BeginDrawing();
		ClearBackground(WHITE); //do zmiany na własne wypełnienie tła
		//rysowanie
		renderer.RenderBuffer();
		EndDrawing();
	}
}

void Engine::Shutdown()
{
	if (is_running) {
		CloseWindow();
		is_running = false;
		cout << "Silnik 2D został zamknięty poprawnie." << endl;
	}
}