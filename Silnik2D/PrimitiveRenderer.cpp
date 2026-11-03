#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

PrimitiveRenderer::PrimitiveRenderer()
{
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
};

void PrimitiveRenderer::DrawRectangle(const Point2D& p1, int width, int height, Color color) const
{
	Point2D p2(p1.GetX() + width, p1.GetY());
	Point2D p3(p1.GetX() + width, p1.GetY() + height);
	Point2D p4(p1.GetX(), p1.GetY() + height);

	DrawLine(p1, p2, color);
	DrawLine(p2, p3, color);
	DrawLine(p3, p4, color);
	DrawLine(p4, p1, color);
	
}

void PrimitiveRenderer::DrawCircle(const Point2D& p, int r, Color color) const
{
	float a, step;
	int x, y;

	step = 1.0 / r;

	for (a = 0; a < PI / 2; a += step) {
		x = r * cos(a) + 0.5;
		y = r * sin(a) + 0.5;

		PutPixel(p.GetX() + x, p.GetY() + y, color);
		PutPixel(p.GetX() - x, p.GetY() + y, color);
		PutPixel(p.GetX() + x, p.GetY() - y, color);
		PutPixel(p.GetX() - x, p.GetY() - y, color);
	}
	//Dorysowanie pikseli na srodku na gorze i na dole zeby zalatac dziury
	PutPixel(p.GetX(), p.GetY() + r, color);
	PutPixel(p.GetX(), p.GetY() - r, color);
}

void PrimitiveRenderer::DrawElipse(const Point2D& p, int xr, int yr, Color color) const
{
	if (xr <= 0 || yr <= 0) return;

	float a, step;
	int x, y;

	step = 1.0 / max(xr, yr);

	for (a = 0; a < PI / 2; a += step) {
		x = xr * cos(a) + 0.5;
		y = yr * sin(a) + 0.5;

		PutPixel(p.GetX() + x, p.GetY() + y, color);
		PutPixel(p.GetX() - x, p.GetY() + y, color);
		PutPixel(p.GetX() + x, p.GetY() - y, color);
		PutPixel(p.GetX() - x, p.GetY() - y, color);
	}

	// Skrajne punkty elipsy
	PutPixel(p.GetX(), p.GetY() + yr, color);
	PutPixel(p.GetX(), p.GetY() - yr, color);
	PutPixel(p.GetX() + xr, p.GetY(), color);
	PutPixel(p.GetX() - xr, p.GetY(), color);
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
