#pragma once
#include "ShapeObject.h"
#include "Point2D.h"
#include "raylib.h"
#include <vector>

class PolygonObject : public ShapeObject
{
private:
    std::vector<Point2D> points;
    Color color;
    bool filled;
    bool closed;

public:
    PolygonObject(const std::vector<Point2D>& points, Color color = BLACK, bool filled = false, bool closed = true);

    const std::vector<Point2D>& GetPoints() const { return points; }
    void SetPoints(const std::vector<Point2D>& points) { this->points = points; }

    Color GetColor() const { return color; }
    PolygonObject& SetColor(Color color) { this->color = color; return *this; }

    void Draw(class PrimitiveRenderer& renderer) const override;
    void Translate(float tx, float ty) override;
    void Rotate(float angle) override;
    void Rotate(float angle, const Point2D& origin) override;
    void Scale(float kx, float ky) override;
    void Scale(float kx, float ky, const Point2D& origin) override;
};