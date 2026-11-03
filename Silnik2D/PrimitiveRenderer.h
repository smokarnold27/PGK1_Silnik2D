#pragma once
#include "raylib.h"
#include "Point2D.h"
#include <vector>

class PrimitiveRenderer
{
private:
	int bufferWidth = 0;
	int bufferHeight = 0;
	mutable std::vector<Color> pixels;

public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	void PutPixel(const Point2D& point, Color color) const;
	void PutPixel(int x, int y, Color color) const;

	Color GetPixelColor(int x, int y) const;

	void ClearBuffer(Color color) const;
	void RenderBuffer() const;
	void FloodFill(int x, int y, Color color) const;

	void DrawLine(const Point2D& p1, const Point2D& p2, Color color) const;
	void DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;
	void DrawRectangle(const Point2D& p1, int width, int height, Color color) const;
	void DrawCircle(const Point2D& center, int radius, Color color) const;
	void DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;
};