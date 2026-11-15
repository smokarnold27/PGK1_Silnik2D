#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

class TriangleObject : public ShapeObject
{
private:
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Color color;
	bool filled;

public:
	TriangleObject(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color = BLACK, bool filled = false);

	void SetVertices(const Point2D& p1, const Point2D& p2, const Point2D& p3) { this->p1 = p1; this->p2 = p2; this->p3 = p3; }

	Color GetColor() const { return color; }
	TriangleObject& SetColor(Color color) { this->color = color; return *this; }

	void Draw(class PrimitiveRenderer& renderer) const override;

	void Translate(float tx, float ty) override;
	void Rotate(float angle) override;
	void Rotate(float angle, const Point2D& origin) override;
	void Scale(float kx, float ky) override;
	void Scale(float kx, float ky, const Point2D& origin) override;
};