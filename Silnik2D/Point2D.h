#pragma once
#include "raylib.h"

class Point2D
{
private:
	int x = 0;
	int y = 0;

public:
	Point2D(int x = 0, int y = 0);

	int GetX() const;
	int GetY() const;
	Point2D& SetX(int x);
	Point2D& SetY(int y);

	void DrawPoint(class PrimitiveRenderer& renderer, Color color) const; // Metoda do rysowania punktu na ekranie przy użyciu renderera
};