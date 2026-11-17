#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

class RectangleObject : public ShapeObject
{
private:
	Point2D topLeft;
	float width;
	float height;
	Color color;
	bool filled;

public:
	RectangleObject(const Point2D& topLeft, float width, float height, Color color = BLACK, bool filled = false);

	Point2D GetTopLeft() const { return topLeft; }
	void SetTopLeft(const Point2D& p) { topLeft = p; }

	Color GetColor() const { return color; }
	RectangleObject& SetColor(Color color) { this->color = color; return *this; }

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void Draw(class PrimitiveRenderer& renderer) const override;
	void Translate(float tx, float ty) override;
	void Rotate(float angle) override;
	void Rotate(float angle, const Point2D& origin) override;
	void Scale(float kx, float ky) override;
	void Scale(float kx, float ky, const Point2D& origin) override;
};