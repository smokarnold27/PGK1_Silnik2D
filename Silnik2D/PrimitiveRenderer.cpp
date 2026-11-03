#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

PrimitiveRenderer::PrimitiveRenderer() {
	bufferWidth = GetScreenWidth();
	bufferHeight = GetScreenHeight();

	pixels.resize(bufferWidth * bufferHeight, WHITE);
}
PrimitiveRenderer ::~PrimitiveRenderer() {}

void PrimitiveRenderer::PutPixel(const Point2D& point, Color color) const {
	PutPixel(point.GetX(), point.GetY(), color);
}

void PrimitiveRenderer::PutPixel(int x, int y, Color color) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return;

	pixels[y * bufferWidth + x] = color;
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
	int x0 = center.GetX();
	int y0 = center.GetY();

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

Color PrimitiveRenderer::GetPixelColor(int x, int y) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return BLANK;

	return pixels[y * bufferWidth + x];
}

void PrimitiveRenderer::ClearBuffer(Color color) const
{
	std::fill(pixels.begin(), pixels.end(), color);
}

void PrimitiveRenderer::RenderBuffer() const
{
	for (int y = 0; y < bufferHeight; y++)
	{
		for (int x = 0; x < bufferWidth; x++)
		{
			DrawPixel(x, y, pixels[y * bufferWidth + x]);
		}
	}
}

void PrimitiveRenderer::FloodFill(int x, int y, Color color) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return;

	Color oldColor = GetPixelColor(x, y);

	auto sameColor = [](Color a, Color b)
		{
			return a.r == b.r &&
				a.g == b.g &&
				a.b == b.b &&
				a.a == b.a;
		};

	if (sameColor(oldColor, color))
		return;

	std::stack<Point2D> points;
	points.push(Point2D(x, y));

	while (!points.empty())
	{
		Point2D p = points.top();
		points.pop();

		int px = p.GetX();
		int py = p.GetY();

		if (px < 0 || px >= bufferWidth ||
			py < 0 || py >= bufferHeight)
			continue;

		if (!sameColor(GetPixelColor(px, py), oldColor))
			continue;

		PutPixel(px, py, color);


		points.push(Point2D(px + 1, py));
		points.push(Point2D(px - 1, py));
		points.push(Point2D(px, py + 1));
		points.push(Point2D(px, py - 1));
	}
}