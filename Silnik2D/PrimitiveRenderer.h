#pragma once
#include "raylib.h"
#include "Point2D.h"

class PrimitiveRenderer
{
public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	void PutPixel(const Point2D& point, Color color) const;
	void PutPixel(int x, int y, Color color) const;

	void DrawLine(const Point2D& p1, const Point2D& p2, Color color) const;
};