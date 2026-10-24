#pragma once
#include <iostream>
#include "raylib.h"
#include "Renderer.h"

using namespace std;

class Engine
{

public:

	void Inicjuj(int screen_width, int screen_height, bool fullscreen, int fps)
	{
		if (fullscreen)
		{
			SetConfigFlags(FLAG_FULLSCREEN_MODE);
		}
		else
		{
			SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		}

		InitWindow(screen_width, screen_height, "OKNO");
		SetTargetFPS(fps);
		Vector2 mouse = GetMousePosition();
		// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))

		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(WHITE);
			Renderer renderer;
			renderer.PutPixel(200, 200);
			//renderer.Draw_line({ 100, 100 }, { 300, 300 });
			renderer.Draw_triangle({ 10, 400 }, { 600, 500 }, { 300, 40 });
			EndDrawing();

		}
	}
};