#include "EllipseObject.h"
#include "PrimitiveRenderer.h"
#include <algorithm>

EllipseObject::EllipseObject(const Point2D& center, int radiusX, int radiusY, Color color, bool filled)
    : center(center), radiusX(radiusX), radiusY(radiusY), color(color), filled(filled) {
}

void EllipseObject::Draw(PrimitiveRenderer& renderer) const
{
    if (filled) {
        renderer.DrawFilledEllipse(center, radiusX, radiusY, color);
    }
    else {
        renderer.DrawEllipse(center, radiusX, radiusY, color);
    }
}

void EllipseObject::Translate(float tx, float ty)
{
    center.Translate(tx, ty);
}

void EllipseObject::Rotate(float angle)
{
    center.Rotate(angle);
}

void EllipseObject::Rotate(float angle, const Point2D& origin)
{
    center.Rotate(angle, origin);
}

void EllipseObject::Scale(float kx, float ky)
{
    radiusX = static_cast<int>(radiusX * std::abs(kx));
    radiusY = static_cast<int>(radiusY * std::abs(ky));
    center.Scale(kx, ky);
}

void EllipseObject::Scale(float kx, float ky, const Point2D& origin)
{
    radiusX = static_cast<int>(radiusX * std::abs(kx));
    radiusY = static_cast<int>(radiusY * std::abs(ky));
    center.Scale(kx, ky, origin);
}