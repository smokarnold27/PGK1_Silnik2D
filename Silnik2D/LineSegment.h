#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

enum class LineAlgorithm {
    DDA,        // Algorytm przyrostowy (DDA)
    Bresenham   // Alternatywny / domyślny algorytm całkowitoliczbowy
};

class LineSegment : public ShapeObject
{
private:
	Point2D startPoint;
	Point2D endPoint;
    Color color;
	LineAlgorithm defaultAlgorithm; // Domyślny algorytm rysowania lini

public:
    LineSegment(const Point2D& p1 = Point2D(0, 0), const Point2D& p2 = Point2D(0, 0), Color color = BLACK, LineAlgorithm algorithm = LineAlgorithm::DDA);
    LineSegment(float x1, float y1, float x2, float y2, Color color = BLACK, LineAlgorithm algorithm = LineAlgorithm::DDA);

    // Odczytanie współrzędnych / końców odcinka
	Point2D GetStartPoint() const { return startPoint; }
    Point2D GetEndPoint() const { return endPoint; }

    // Zmodyfikowanie współrzędnych / końców odcinka
	void SetStartPoint(const Point2D& p) { startPoint = p; }
    void SetEndPoint(const Point2D& p) { endPoint = p; }
    void SetSegment(const Point2D& p1, const Point2D& p2) { startPoint = p1; endPoint = p2; }
    
	Color GetColor() const { return color; }
	LineSegment& SetColor(Color color) { this->color = color; return *this; }

    // Narysowanie odcinka z wyborem algorytmu przy użyciu klasy PrimitiveRenderer
    void Draw(class PrimitiveRenderer& renderer) const override;
	
	void Translate(float tx, float ty) override;
	void Rotate(float angle) override;
	void Rotate(float angle, const Point2D& origin) override;
	void Scale(float kx, float ky) override;
	void Scale(float kx, float ky, const Point2D& origin) override;
};

