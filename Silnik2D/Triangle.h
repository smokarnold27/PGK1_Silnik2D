#pragma once
#include "ShapeObject.h"
#include "raylib.h"
#include "Point2D.h"

class Triangle :
    public ShapeObject
{
public:
	Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color = BLACK);
	virtual void Draw() const override;
	virtual void Translate(float dx, float dy) override;
	virtual void Rotate(float angle) override;
	virtual void Scale(float sx, float sy) override;

private:
	Point2D m_p1, m_p2, m_p3;
};

