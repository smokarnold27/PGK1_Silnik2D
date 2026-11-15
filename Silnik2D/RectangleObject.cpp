#include "RectangleObject.h"
#include "PrimitiveRenderer.h"

RectangleObject::RectangleObject(const Point2D& topLeft, float width, float height, Color color, bool filled)
	: topLeft(topLeft), width(width), height(height), color(color), filled(filled) {}

void RectangleObject::Draw(PrimitiveRenderer& renderer) const
{
	if (filled) {
		renderer.DrawFilledRectangle(topLeft, static_cast<int>(width), static_cast<int>(height), color);
	}
	else {
		renderer.DrawRectangle(topLeft, static_cast<int>(width), static_cast<int>(height), color);
	}
}

void RectangleObject::Translate(float tx, float ty)
{
	topLeft.Translate(tx, ty);
}

void RectangleObject::Rotate(float angle)
{
	topLeft.Rotate(angle);
}

void RectangleObject::Rotate(float angle, const Point2D& origin)
{
	topLeft.Rotate(angle, origin);
}

void RectangleObject::Scale(float kx, float ky)
{
	width *= kx;
	height *= ky;
	topLeft.Scale(kx, ky);
}

void RectangleObject::Scale(float kx, float ky, const Point2D& origin)
{
	width *= kx;
	height *= ky;
	topLeft.Scale(kx, ky, origin);
}