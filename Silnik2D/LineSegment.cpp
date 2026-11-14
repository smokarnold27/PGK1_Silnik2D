#include "LineSegment.h"
#include "PrimitiveRenderer.h"

LineSegment::LineSegment(const Point2D& p1, const Point2D& p2)
    : startPoint(p1), endPoint(p2) {
}

LineSegment::LineSegment(int x1, int y1, int x2, int y2)
    : startPoint(x1, y1), endPoint(x2, y2) {
}

Point2D LineSegment::GetStartPoint() const {
    return startPoint;
}

Point2D LineSegment::GetEndPoint() const {
    return endPoint;
}

void LineSegment::SetStartPoint(const Point2D& p) {
    startPoint = p;
}

void LineSegment::SetEndPoint(const Point2D& p) {
    endPoint = p;
}

void LineSegment::SetSegment(const Point2D& p1, const Point2D& p2) {
    startPoint = p1;
    endPoint = p2;
}

void LineSegment::Draw(PrimitiveRenderer& renderer, Color color, LineAlgorithm algorithm) const {
    if (algorithm == LineAlgorithm::DDA) {
        renderer.DrawLine(startPoint, endPoint, color); // Wywołuje Wasz algorytm przyrostowy (DDA)
    }
    else {
        renderer.DrawLineBresenham(startPoint, endPoint, color); // Wywołuje algorytm Bresenhama jako domyślny/alternatywny
    }
}