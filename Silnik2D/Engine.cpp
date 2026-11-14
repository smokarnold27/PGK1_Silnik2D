#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"

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
	return true;
}

void Engine::Run() 
{
	PrimitiveRenderer renderer;
	Point2D p1(500, 100);
	Point2D p2(100, 400);

	Point2D p3(150, 300);
	Point2D p4(700, 500);
	Point2D p5(280, 180);

	Point2D p6(200, 600);

	renderer.ClearBuffer(WHITE);

	std::vector<Point2D> polyPoints = {
	Point2D(100, 100),
	Point2D(250, 80),
	Point2D(300, 200),
	Point2D(120, 220)
	};
	renderer.DrawPolyline(polyPoints, PURPLE, true); // true = linia zamknięta
	renderer.DrawLine(p1, p2, RED);

	renderer.DrawTriangle(p3, p4, p5, BLUE);
	renderer.DrawRectangle(p6, 300, 100, GREEN);
	renderer.DrawCircle({ 200,200 }, 50, PINK);
	renderer.DrawEllipse({ 400,350 }, 100, 40, BLACK);
	std::vector<Point2D> validPolygon = {
		Point2D(520, 80),
		Point2D(680, 60),
		Point2D(720, 180),
		Point2D(610, 140), // wklęsły wierzchołek
		Point2D(540, 200)
	};
	renderer.DrawPolygon(validPolygon, DARKGREEN);
	// 2. Test łamanej wiązanej (krawędzie się przecinają - metoda przerwie działanie i NIC nie narysuje)
	std::vector<Point2D> intersectingPolygon = {
		Point2D(550, 250),
		Point2D(700, 380), // przekątna 1
		Point2D(700, 250),
		Point2D(550, 380)  // przekątna 2 (przecina pierwszą)
	};
	renderer.DrawPolygon(intersectingPolygon, MAROON);

	renderer.DrawFilledTriangle(Point2D(220, 530), Point2D(320, 450), Point2D(350, 530), SKYBLUE);
	renderer.DrawFilledRectangle(Point2D(50, 450), 120, 80, ORANGE);
	renderer.DrawFilledCircle(Point2D(450, 490), 45, MAROON);
	renderer.DrawFilledEllipse(Point2D(630, 490), 80, 40, MAGENTA);
	std::vector<Point2D> filledPoly = {
		Point2D(60, 260),
		Point2D(160, 240),
		Point2D(130, 310),
		Point2D(170, 370),
		Point2D(50, 350)
	};
	renderer.DrawFilledPolygon(filledPoly, LIME);
	std::vector<Point2D> parityTestPolygon = {
		Point2D(380, 120), // lokalne maksimum (szczyt)
		Point2D(440, 220),
		Point2D(480, 150), // drugi szczyt
		Point2D(520, 260),
		Point2D(440, 260), // krawędź pozioma na dole
		Point2D(410, 220), // wklęsły wierzchołek dokładnie na tej samej wysokości y=220 co punkt (440, 220)
		Point2D(350, 280)
	};
	renderer.DrawFilledPolygon(parityTestPolygon, BEIGE);
	

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
		//obsługa myszy i klawiatury
		/*if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            //kliknięcie myszką w danym punkcie (x, y)
        }*/

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