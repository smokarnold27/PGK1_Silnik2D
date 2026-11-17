#pragma once

#include "DrawableObject.h"
#include "TransformableObject.h"
#include "BitmapHandler.h"
#include "Point2D.h"
#include "RectangleObject.h"
#include <vector>

class BitmapObject : public DrawableObject,
    public TransformableObject
{
protected:
    struct BitmapPart
    {
        BitmapHandler bitmap;
        Point2D offset;
    };

    std::vector<BitmapPart> bitmaps;

    Point2D position{ 0.0f, 0.0f };
    Point2D axisX{ 1.0f, 0.0f };
    Point2D axisY{ 0.0f, 1.0f };

    Point2D TransformPoint(
        const Point2D& point) const;

    void DrawPart(
        PrimitiveRenderer& renderer,
        const BitmapPart& part,
        const RectangleObject& source) const;

public:
    BitmapObject() = default;
    virtual ~BitmapObject() = default;

    virtual bool AddBitmap(
        const char* filename,
        const Point2D& offset = Point2D());

    void RemoveBitmap(int index);
    void ClearBitmaps();
    int GetBitmapCount() const;

    void Draw(
        PrimitiveRenderer& renderer) const override;

    void Translate(float tx, float ty) override;

    void Rotate(float angle) override;

    void Rotate(
        float angle,
        const Point2D& origin) override;

    void Scale(float kx, float ky) override;

    void Scale(
        float kx,
        float ky,
        const Point2D& origin) override;
};