#include "CircleObject.h"
#include "PrimitiveRenderer.h"
#include <algorithm>

CircleObject::CircleObject(const Point2D& center, int radius, Color color, bool filled)
    : center(center), radius(radius), color(color), filled(filled) {
}

void CircleObject::Draw(PrimitiveRenderer& renderer) const
{
    if (filled) {
        renderer.DrawFilledCircle(center, radius, color);
    }
    else {
        renderer.DrawCircle(center, radius, color);
    }
}

void CircleObject::Translate(float tx, float ty)
{
    center.Translate(tx, ty);
}

void CircleObject::Rotate(float angle)
{
    center.Rotate(angle);
}

void CircleObject::Rotate(float angle, const Point2D& origin)
{
    center.Rotate(angle, origin);
}

void CircleObject::Scale(float kx, float ky)
{
    radius = static_cast<int>(radius * std::abs(kx));
    center.Scale(kx, ky);
}

void CircleObject::Scale(float kx, float ky, const Point2D& origin)
{
    radius = static_cast<int>(radius * std::abs(kx));
    center.Scale(kx, ky, origin);
}