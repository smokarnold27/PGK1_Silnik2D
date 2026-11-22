#include "LineSegment.h"
#include "PrimitiveRenderer.h"

LineSegment::LineSegment(const Point2D& p1, const Point2D& p2, Color color, LineAlgorithm algorithm)
    : startPoint(p1), endPoint(p2), color(color), defaultAlgorithm(algorithm) {}

LineSegment::LineSegment(float x1, float y1, float x2, float y2, Color color, LineAlgorithm algorithm)
    : startPoint(x1, y1), endPoint(x2, y2), color(color), defaultAlgorithm(algorithm) {}

void LineSegment::Draw(PrimitiveRenderer& renderer) const {
    if (defaultAlgorithm == LineAlgorithm::DDA) {
        renderer.DrawLine(startPoint, endPoint, color); // Wywołuje algorytm przyrostowy (DDA)
    }
    else {
        renderer.DrawLineBresenham(startPoint, endPoint, color); // Wywołuje algorytm Bresenhama
    }
}

void LineSegment::Translate(float tx, float ty) {
    startPoint.Translate(tx, ty);
    endPoint.Translate(tx, ty);
}

void LineSegment::Rotate(float angle) {
    startPoint.Rotate(angle);
    endPoint.Rotate(angle);
}

void LineSegment::Rotate(float angle, const Point2D& origin) {
    startPoint.Rotate(angle, origin);
    endPoint.Rotate(angle, origin);
}

void LineSegment::Scale(float kx, float ky) {
    startPoint.Scale(kx, ky);
    endPoint.Scale(kx, ky);
}

void LineSegment::Scale(float kx, float ky, const Point2D& origin) {
    startPoint.Scale(kx, ky, origin);
    endPoint.Scale(kx, ky, origin);
}