#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include <cmath>

Point2D::Point2D(float x, float y, Color color) : x(x), y(y), color(color) {}

int Point2D::GetX() const
{
    return static_cast<int>(std::round(x));
}

int Point2D::GetY() const
{
    return static_cast<int>(std::round(y));
}

Point2D& Point2D::SetX(float x) 
{
    this->x = x;
	return *this;
}

Point2D& Point2D::SetY(float y) 
{
    this->y = y;
	return *this;
}

void Point2D::DrawPoint(PrimitiveRenderer& renderer, Color color) const 
{
    renderer.PutPixel(GetX(), GetY(), color);
}

void Point2D::Draw(PrimitiveRenderer& renderer) const
{
    renderer.PutPixel(GetX(), GetY(), color);
}

void Point2D::Translate(float tx, float ty)
{
    x += tx;
    y += ty;
}

void Point2D::Rotate(float angle)
{
    // Rotacja względem początku układu (0,0)
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    float newX = x * cosA - y * sinA;
    float newY = x * sinA + y * cosA;

    x = newX;
    y = newY;
}

void Point2D::Rotate(float angle, const Point2D& origin)
{
    // Rotacja względem dowolnego punktu (x0, y0)
    float x0 = origin.GetExactX();
    float y0 = origin.GetExactY();

    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    float newX = x0 + (x - x0) * cosA - (y - y0) * sinA;
    float newY = y0 + (x - x0) * sinA + (y - y0) * cosA;

    x = newX;
    y = newY;
}

void Point2D::Scale(float kx, float ky)
{
    // Jednokładność względem początku układu (0,0)
    x *= kx;
    y *= ky;
}

void Point2D::Scale(float kx, float ky, const Point2D& origin)
{
    // Jednokładność względem dowolnego punktu (x0, y0
    float x0 = origin.GetExactX();
    float y0 = origin.GetExactY();

    x = x * kx + (1.0f - kx) * x0;
    y = y * ky + (1.0f - ky) * y0;
}