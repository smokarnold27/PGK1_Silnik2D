#pragma once
#include "ShapeObject.h"
#include "raylib.h"

class Point2D : public ShapeObject
{
private:
	float x = 0.0f;
	float y = 0.0f;
	Color color;

public:
	Point2D(float x = 0.0f, float y = 0.0f, Color color = BLACK);

	int GetX() const;
	int GetY() const;
	float GetExactX() const { return x; }
	float GetExactY() const { return y; }

	Point2D& SetX(float x);
	Point2D& SetY(float y);

	Color GetColor() const { return color; }
	Point2D& SetColor(Color color) { this->color = color; return *this; }

	void DrawPoint(class PrimitiveRenderer& renderer, Color color) const; // Metoda do rysowania punktu na ekranie przy użyciu renderera

	void Draw(PrimitiveRenderer& renderer) const override; // Implementacja metody Draw z klasy ShapeObject
	void Translate(float tx, float ty) override; // Implementacja translacji z klasy TransformableObject
	void Rotate(float angle) override; // Implementacja rotacji z klasy TransformableObject
	void Rotate(float angle, const Point2D& origin) override; // Implementacja rotacji względem punktu z klasy TransformableObject
	void Scale(float kx, float ky) override; // Implementacja skalowania z klasy TransformableObject
	void Scale(float kx, float ky, const Point2D& origin) override; // Implementacja skalowania względem punktu z klasy TransformableObject
};
