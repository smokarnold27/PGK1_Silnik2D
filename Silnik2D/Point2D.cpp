#include "Point2D.h"
#include "PrimitiveRenderer.h"

Point2D::Point2D(int x, int y) : x(x), y(y) {}

int Point2D::GetX() const
{
    return x;
}

int Point2D::GetY() const
{
    return y;
}

Point2D& Point2D::SetX(int x) 
{
    this->x = x;
	return *this;
}

Point2D& Point2D::SetY(int y) 
{
    this->y = y;
	return *this;
}

void Point2D::DrawPoint(PrimitiveRenderer& renderer, Color color) const 
{
    renderer.PutPixel(*this, color);
}
