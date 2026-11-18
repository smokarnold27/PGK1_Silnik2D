#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "TriangleObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "EllipseObject.h"
#include "PolygonObject.h"
#include "Player.h"
#include "BitmapObject.h"
#include "Path.h"
#include "FlyObject.h"
#include <vector>

using namespace std;

static Player* player_ptr = nullptr; // Wskaźnik na obiekt gracza

// Siatka rzeki: 10 kolumn (X: 80..720), 9 wierszy (Y: 12..588)
static bool lily_grid[10][9] = { false };
static const Point2D START_POS(8, 268); // Pozycja startowa na lewym trawniku

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
		//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	}

	InitWindow(screen_width, screen_height, "Silnik 2D");
	if (!IsWindowReady()) {
		cerr << "Błąd! Не udało się zainicjalizować okna biblioteki graficznej!" << endl;
		return false;
	}
	SetTargetFPS(target_fps);
	is_running = true;

	objects.clear();
	player_ptr = nullptr;

	/*

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
	objects.push_back(make_unique<PolygonObject>(polyPoints, DARKGREEN, false, true));

	// Wielokąt (wypełniony)
	vector<Point2D> filledPolyPoints = {
		Point2D(60, 260),
		Point2D(160, 240),
		Point2D(130, 310),
		Point2D(170, 370),
		Point2D(50, 350)
	};
	objects.push_back(make_unique<PolygonObject>(filledPolyPoints, LIME, true, true));

	*/


	// proceduralne generowanie lilii przez zewnętrzny moduł Path
	srand(static_cast<unsigned int>(time(nullptr)));
	GenerateLilies(lily_grid, objects);

	// Dodanie obiektu gracza (sprite) na początkowej pozycji (380, 280) z rozmiarem 64 i prędkością 4
	auto player = make_unique<Player>(START_POS, 64, PURPLE, 8);
	player_ptr = player.get();
	bitmap_objects.push_back(move(player));

	auto bitmapObj = make_unique<BitmapObject>();
	bitmapObj->AddBitmap("../BITMAPA.png", Point2D(0, 0));
	bitmap_objects.push_back(move(bitmapObj));

	flies.clear();
	for (int i = 0; i < 5; ++i) {
		// Losowa pozycja startowa nad woda (X: 100..600, Y: 100..400)
		float rx = static_cast<float>(80 + rand() % 500);
		float ry = static_cast<float>(50 + rand() % 400);

		// Losowa predkosc i kierunek w skos (np. od 60 do 120 px/s)
		float vx = (rand() % 2 == 0 ? 1.0f : -1.0f) * (60.0f + static_cast<float>(rand() % 60));
		float vy = (rand() % 2 == 0 ? 1.0f : -1.0f) * (60.0f + static_cast<float>(rand() % 60));

		flies.push_back(make_unique<FlyObject>(Point2D(rx, ry), vx, vy));
	}

	return true;
}

void Engine::Run()
{
	PrimitiveRenderer renderer;

	while (is_running && !WindowShouldClose())
	{
		float delta_time = GetFrameTime();
		if (IsKeyPressed(KEY_ESCAPE)) {
			is_running = false;
		}

		// Aktualizacja pozycji much
		for (auto& fly : flies) {
			fly->Update(delta_time);
		}

		// Obsługa wypełnień (w tym momencie w buforze nie ma gracza, więc wypełniamy czyste tło/figury)
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mouse = GetMousePosition();
			renderer.FloodFill(static_cast<int>(mouse.x), static_cast<int>(mouse.y), YELLOW);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			Vector2 mouse = GetMousePosition();
			renderer.BorderFill(static_cast<int>(mouse.x), static_cast<int>(mouse.y), SKYBLUE, BLACK);
		}

		// Aktualizacja pozycji gracza
		if (player_ptr) {
			player_ptr->Update(delta_time);
			Point2D pos = player_ptr->GetPosition();

			// Jeśli żaba umiera, pozwalamy jej lecieć w dół poza ekran, omijając ograniczenia okna
			if (player_ptr->IsDying()) {
				if (pos.GetExactY() >= 600.0f) {
					player_ptr->SetPosition(START_POS);
					player_ptr->ResetDeath();
					pos = player_ptr->GetPosition();
				}
			}
			else {
				//zabezpieczenie przed wyjściem poza okno
				float px_f = pos.GetExactX();
				float py_f = pos.GetExactY();
				if (px_f < 0) px_f = 0;
				if (px_f > 800 - 64) px_f = 800 - 64;
				if (py_f < 0) py_f = 0;
				if (py_f > 600 - 64) py_f = 600 - 64;

				//jesli wyjdzie poza okno
				if (px_f != pos.GetExactX() || py_f != pos.GetExactY()) {
					player_ptr->SetPosition(Point2D(px_f, py_f));
					pos = player_ptr->GetPosition();
				}

				//srodek zaby
				int cx = pos.GetX() + 32;
				int cy = pos.GetY() + 32;

				// Sprawdzenie kolizji zaby z muchami
				Point2D frogPos = player_ptr->GetPosition();
				bool hitFly = false;
				for (const auto& fly : flies) {
					Point2D flyPos = fly->GetPosition();
					if (frogPos.GetExactX() < flyPos.GetExactX() + 32 &&
						frogPos.GetExactX() + 64 > flyPos.GetExactX() &&
						frogPos.GetExactY() < flyPos.GetExactY() + 32 &&
						frogPos.GetExactY() + 64 > flyPos.GetExactY())
					{
						hitFly = true;
						break;
					}
				}

				// Obliczenie kolumny i wiersza w siatce lilii
				int col = -1;
				int row = -1;
				if (cx >= 80 && cx < 720) {
					col = (cx - 80) / 64;
					row = (cy - 12) / 64;
				}

				// Sprawdzenie warunków śmierci (mucha lub woda)
				if (hitFly || cy < 12 || cy >= 588 || (cx >= 80 && cx < 720 && (row < 0 || row >= 9 || !lily_grid[col][row]))) {
					player_ptr->StartDeath();
				}
				//meta i tp na start + nowy uklad lilii
				else if (cx >= 720) {
					cout << "Wygrana" << endl;

					//usuniecie starych lilii z wektora obiektow
					objects.clear();

					//generowanie nowej ścieżki przez moduł Path
					GenerateLilies(lily_grid, objects);

					//tp gracza na start
					player_ptr->SetPosition(START_POS);
					pos = player_ptr->GetPosition();
				}
			}
		}

		// renderowanie klatki na czysto
		renderer.ClearBuffer(WHITE);

		// Rysowanie tla (bitmapy)
		for (const auto& bmp : bitmap_objects) {
			if (!dynamic_cast<Player*>(bmp.get())) {
				bmp->Draw(renderer);
			}
		}

		// Rysowanie lilii
		for (const auto& obj : objects) {
			if (!dynamic_cast<Player*>(obj.get())) {
				obj->Draw(renderer);
			}
		}

		// Rysowanie much
		for (const auto& fly : flies) {
			fly->Draw(renderer);
		}

		// Rysowanie gracza
		if (player_ptr) {
			player_ptr->Draw(renderer);
		}

		// Wyświetlenie gotowego bufora na ekranie
		BeginDrawing();
		ClearBackground(WHITE);
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