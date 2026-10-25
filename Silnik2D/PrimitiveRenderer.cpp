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