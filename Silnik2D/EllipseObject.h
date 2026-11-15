#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"

class EllipseObject : public ShapeObject
{
private:
    Point2D center;
    int radiusX;
    int radiusY;
    Color color;
    bool filled;

public:
    EllipseObject(const Point2D& center, int radiusX, int radiusY, Color color = BLACK, bool filled = false);

    Point2D GetCenter() const { return center; }
    void SetCenter(const Point2D& center) { this->center = center; }

    Color GetColor() const { return color; }
    EllipseObject& SetColor(Color color) { this->color = color; return *this; }

    void Draw(class PrimitiveRenderer& renderer) const override;
    void Translate(float tx, float ty) override;
    void Rotate(float angle) override;
    void Rotate(float angle, const Point2D& origin) override;
    void Scale(float kx, float ky) override;
    void Scale(float kx, float ky, const Point2D& origin) override;
};