#pragma once
#include "Point2D.h"
#include "raylib.h"

enum class LineAlgorithm {
    DDA,        // Algorytm przyrostowy (DDA)
    Bresenham   // Alternatywny / domyślny algorytm całkowitoliczbowy
};

class LineSegment
{
private:
	Point2D startPoint;
	Point2D endPoint;

public:
    LineSegment(const Point2D& p1 = Point2D(0, 0), const Point2D& p2 = Point2D(0, 0));
    LineSegment(int x1, int y1, int x2, int y2);

    // Odczytanie współrzędnych / końców odcinka
    Point2D GetStartPoint() const;
    Point2D GetEndPoint() const;

    // Zmodyfikowanie współrzędnych / końców odcinka
    void SetStartPoint(const Point2D& p);
    void SetEndPoint(const Point2D& p);
    void SetSegment(const Point2D& p1, const Point2D& p2);

    // Narysowanie odcinka z wyborem algorytmu przy użyciu klasy PrimitiveRenderer
    void Draw(class PrimitiveRenderer& renderer, Color color, LineAlgorithm algorithm = LineAlgorithm::DDA) const;
};

