#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>
using namespace std;

PrimitiveRenderer::PrimitiveRenderer() {}
PrimitiveRenderer ::~PrimitiveRenderer() {}

void PrimitiveRenderer::PutPixel(const Point2D& point, Color color) const {
    DrawPixel(point.GetX(), point.GetY(), color);
}

void PrimitiveRenderer::PutPixel(int x, int y, Color color) const
{
	DrawPixel(x, y, color);
}

void PrimitiveRenderer::DrawLine(const Point2D& p1, const Point2D& p2, Color color) const
{
    int x0 = p1.GetX();
    int y0 = p1.GetY();
    int x1 = p2.GetX();
    int y1 = p2.GetY();

    int dx = x1 - x0;
    int dy = y1 - y0;

	if (abs(dy) <= abs(dx)) { // Linia jest bardziej pozioma niż pionowa (|m| <= 1), std::abs() jest używane do obliczenia wartości bezwzględnej
        if (x0 > x1) {
            swap(x0, x1);
			swap(y0, y1);
        }
		dx = x1 - x0;
        dy = y1 - y0;

        if (dx == 0) {
            PutPixel(x0, y0, color);
            return;
        }

		float m = static_cast<float>(dy) / dx;
		float y = static_cast<float>(y0);

		for (int x = x0; x <= x1; x++) {
			PutPixel(x, static_cast<int>(round(y)), color);
			y += m;
		}
    }
	else { // Linia jest bardziej pionowa niż pozioma
        if (y0 > y1) {
            swap(x0, x1);
            swap(y0, y1);
        }
		dx = x1 - x0;
		dy = y1 - y0;

		if (dy == 0) {
			PutPixel(x0, y0, color);
			return;
		}

		float m_prime = static_cast<float>(dx) / dy;
		float x = static_cast<float>(x0);

		for (int y = y0; y <= y1; y++) {
			PutPixel(static_cast<int>(round(x)), y, color);
			x += m_prime;
		}
    }
}

void PrimitiveRenderer::DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const
{
	DrawLine(p1,p2,color);
	DrawLine(p1,p3,color);
	DrawLine(p2,p3,color);
}

void PrimitiveRenderer::DrawRectangle(const Point2D& p1, int width, int height, Color color) const
{
	int w = std::abs(width);
	int h = std::abs(height);

	int startX = (width < 0) ? p1.GetX() - w : p1.GetX();
	int startY = (height < 0) ? p1.GetY() - h : p1.GetY();

	Point2D p2(startX + w, startY);
	Point2D p3(startX + w, startY + h);
	Point2D p4(startX, startY + h);
	Point2D topLeft(startX, startY);

	DrawLine(topLeft, p2, color);
	DrawLine(p2, p3, color);
	DrawLine(p3, p4, color);
	DrawLine(p4, topLeft, color);
}

void PrimitiveRenderer::DrawCircle(const Point2D& center, int radius, Color color) const
{
	if (radius <= 0) return;

	float a, step;
	int x, y;

	step = 1.0f / radius;
	int x0 = p.GetX();
	int y0 = p.GetY();

	for (a = 0; a <= PI / 4; a += step) {
		x = static_cast<int>(radius * cos(a) + 0.5f);
		y = static_cast<int>(radius * sin(a) + 0.5f);

		// 4 symetrie podstawowe
		PutPixel(x0 + x, y0 + y, color);
		PutPixel(x0 - x, y0 + y, color);
		PutPixel(x0 + x, y0 - y, color);
		PutPixel(x0 - x, y0 - y, color);

		// 4 symetrie wynikające z zamiany x i y (ośmiokrotna symetria)
		PutPixel(x0 + y, y0 + x, color);
		PutPixel(x0 - y, y0 + x, color);
		PutPixel(x0 + y, y0 - x, color);
		PutPixel(x0 - y, y0 - x, color);
	}
}

void PrimitiveRenderer::DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const
{
	if (radiusX <= 0 || radiusY <= 0) return;

	float a, step;
	int x, y;

	step = 1.0f / max(radiusX, radiusY);
	int x0 = center.GetX();
	int y0 = center.GetY();

	for (a = 0; a < PI / 2; a += step)
	{
		x = static_cast<int>(radiusX * cos(a) + 0.5f);
		y = static_cast<int>(radiusY * sin(a) + 0.5f);

		// 4 symetrie
		PutPixel(x0 + x, y0 + y, color);
		PutPixel(x0 - x, y0 + y, color);
		PutPixel(x0 + x, y0 - y, color);
		PutPixel(x0 - x, y0 - y, color);
	}
	// Dorysowanie skrajnych punktów osiowych, aby domknąć elipsę na krawędziach
	PutPixel(x0, y0 + radiusY, color);
	PutPixel(x0, y0 - radiusY, color);
	PutPixel(x0 + radiusX, y0, color);
	PutPixel(x0 - radiusX, y0, color);
}

void PrimitiveRenderer::FillWithColor(const Point2D& p1, Color color, Color bgcolor) const
{
	Image screenImage = LoadImageFromTexture(LoadRenderTexture(800, 600).texture);
	Color pixelColor = GetImageColor(screenImage, p1.GetX(), p1.GetY());
	UnloadImage(screenImage);

	if (color.r == pixelColor.r && color.g == pixelColor.g && color.b == pixelColor.b && color.a == pixelColor.a)
	{
		return;
	}
	if (bgcolor.r != pixelColor.r && bgcolor.g != pixelColor.g && bgcolor.b != pixelColor.b && bgcolor.a != pixelColor.a)
	{
		return;
	}
}