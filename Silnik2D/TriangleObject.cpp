#include "TriangleObject.h"
#include "PrimitiveRenderer.h"

TriangleObject::TriangleObject(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color, bool filled)
	: p1(p1), p2(p2), p3(p3), color(color), filled(filled) {}

void TriangleObject::Draw(PrimitiveRenderer& renderer) const
{
	if (filled) {
		renderer.DrawFilledTriangle(p1, p2, p3, color);
	}
	else {
		renderer.DrawTriangle(p1, p2, p3, color);
	}
}

void TriangleObject::Translate(float tx, float ty)
{
	p1.Translate(tx, ty);
	p2.Translate(tx, ty);
	p3.Translate(tx, ty);
}

void TriangleObject::Rotate(float angle)
{
	p1.Rotate(angle);
	p2.Rotate(angle);
	p3.Rotate(angle);
}

void TriangleObject::Rotate(float angle, const Point2D& origin)
{
	p1.Rotate(angle, origin);
	p2.Rotate(angle, origin);
	p3.Rotate(angle, origin);
}

void TriangleObject::Scale(float kx, float ky)
{
	p1.Scale(kx, ky);
	p2.Scale(kx, ky);
	p3.Scale(kx, ky);
}

void TriangleObject::Scale(float kx, float ky, const Point2D& origin)
{
	p1.Scale(kx, ky, origin);
	p2.Scale(kx, ky, origin);
	p3.Scale(kx, ky, origin);
}