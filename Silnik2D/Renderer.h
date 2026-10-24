#pragma once
#include "raylib.h"
#include <vector>

using namespace std;

class Renderer
{

	struct Point {
		int x;
		int y;
	};

public:

	void PutPixel(int x, int y)
	{
		DrawPixel(x, y, Color{ 67, 0, 200, 255 });
	}

	void Draw_line(Point p1, Point p2)
	{
		int x = 0;
		float dy, dx, y, m;
		dy = p2.y - p1.y;
		dx = p2.x - p1.x;
		m = dy / dx;
		y = p1.y;

		for (x = p1.x;x <= p2.x;x++) {
			PutPixel(x, y);
			y += m;
		}
	}

	void Draw_triangle(Point p1, Point p2, Point p3) {
		Draw_line(p1, p2);
		Draw_line(p2, p3);
		Draw_line(p1, p3);
	}
};