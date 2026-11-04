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

	renderer.DrawLine(p1, p2, RED);
	renderer.DrawTriangle(p3, p4, p5, BLUE);
	renderer.DrawRectangle(p6, 300, 100, GREEN);
	renderer.DrawCircle({ 200,200 }, 50, PINK);
	renderer.DrawEllipse({ 400,350 }, 100, 40, BLACK);
	

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

			renderer.FloodFill(
				static_cast<int>(mouse.x),
				static_cast<int>(mouse.y),
				RED
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