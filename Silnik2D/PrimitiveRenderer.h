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
	void DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;
	void DrawRectangle(const Point2D& p1, int width, int height, Color color) const;
	void DrawCircle(const Point2D& center, int radius, Color color) const;
	void DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;
	void FillWithColor(const Point2D& p1, Color color, Color bgcolor) const;
};