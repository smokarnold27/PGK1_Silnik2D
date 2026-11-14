#pragma once
#include "raylib.h"
#include "Point2D.h"
#include "LineSegment.h"
#include <vector>

class PrimitiveRenderer
{
private:
	int bufferWidth = 0;
	int bufferHeight = 0;
	mutable std::vector<Color> pixels;
	// Pomocnicze metody geometryczne do wykrywania przecięć odcinków
	int Orientation(const Point2D& p, const Point2D& q, const Point2D& r) const;
	bool OnSegment(const Point2D& p, const Point2D& q, const Point2D& r) const;
	bool DoSegmentsIntersect(const LineSegment& s1, const LineSegment& s2) const;

public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	void PutPixel(const Point2D& point, Color color) const;
	void PutPixel(int x, int y, Color color) const;

	Color GetPixelColor(int x, int y) const;

	void ClearBuffer(Color color) const;
	void RenderBuffer() const;
	void FloodFill(int x, int y, Color color) const;
	void BorderFill(int x, int y, Color fillColor, Color borderColor) const;

	void DrawLine(const Point2D& p1, const Point2D& p2, Color color) const;
	void DrawLineBresenham(const Point2D& p1, const Point2D& p2, Color color) const; // Rysowanie linii łamanej (otwartej lub zamkniętej) na podstawie zbioru punktów
	void DrawPolyline(const std::vector<Point2D>& points, Color color, bool closed = false) const; // Rysowanie linii łamanej na podstawie zbioru gotowych odcinków (LineSegment)
	void DrawPolyline(const std::vector<LineSegment>& segments, Color color) const;
	
	void DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;
	void DrawRectangle(const Point2D& p1, int width, int height, Color color) const;
	void DrawCircle(const Point2D& center, int radius, Color color) const;
	void DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;
	// Rysowanie wielokąta (łamanej zwyczajnej zamkniętej) - przerywa, jeśli krawędzie się przecinają
	void DrawPolygon(const std::vector<Point2D>& points, Color color) const;
	void DrawPolygon(const std::vector<LineSegment>& segments, Color color) const;

	void DrawFilledTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const;
	void DrawFilledRectangle(const Point2D& p1, int width, int height, Color color) const;
	void DrawFilledCircle(const Point2D& center, int radius, Color color) const;
	void DrawFilledEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const;
	void DrawFilledPolygon(const std::vector<Point2D>& points, Color color) const;
};