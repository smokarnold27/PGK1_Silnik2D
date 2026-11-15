#include "PolygonObject.h"
#include "PrimitiveRenderer.h"

PolygonObject::PolygonObject(const std::vector<Point2D>& points, Color color, bool filled, bool closed)
    : points(points), color(color), filled(filled), closed(closed) {
}

void PolygonObject::Draw(PrimitiveRenderer& renderer) const
{
    if (filled && closed) {
        renderer.DrawFilledPolygon(points, color);
    }
    else {
        renderer.DrawPolyline(points, color, closed);
    }
}

void PolygonObject::Translate(float tx, float ty)
{
    for (auto& pt : points) {
        pt.Translate(tx, ty);
    }
}

void PolygonObject::Rotate(float angle)
{
    for (auto& pt : points) {
        pt.Rotate(angle);
    }
}

void PolygonObject::Rotate(float angle, const Point2D& origin)
{
    for (auto& pt : points) {
        pt.Rotate(angle, origin);
    }
}

void PolygonObject::Scale(float kx, float ky)
{
    for (auto& pt : points) {
        pt.Scale(kx, ky);
    }
}

void PolygonObject::Scale(float kx, float ky, const Point2D& origin)
{
    for (auto& pt : points) {
        pt.Scale(kx, ky, origin);
    }
}