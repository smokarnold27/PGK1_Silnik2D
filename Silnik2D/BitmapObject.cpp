#include "BitmapObject.h"
#include "PrimitiveRenderer.h"

bool BitmapObject::AddBitmap(const char* filename, const Point2D& offset)
{
    BitmapPart part;

    if (!part.bitmap.load(filename))
        return false;

    part.offset = offset;

    bitmaps.push_back(part);

    return true;
}

void BitmapObject::RemoveBitmap(int index)
{
    if (index < 0 || index >= GetBitmapCount())
        return;

    bitmaps.erase(bitmaps.begin() + index);
}

void BitmapObject::ClearBitmaps()
{
    bitmaps.clear();
}

int BitmapObject::GetBitmapCount() const
{
    return static_cast<int>(bitmaps.size());
}

Point2D BitmapObject::TransformPoint(const Point2D& point) const
{
    float x = point.GetExactX();
    float y = point.GetExactY();

    float px = position.GetExactX();
    float py = position.GetExactY();

    return Point2D(px + x * (axisX.GetExactX() - px) + y * (axisY.GetExactX() - px), py + x * (axisX.GetExactY() - py) + y * (axisY.GetExactY() - py));
}

void BitmapObject::DrawPart(PrimitiveRenderer& renderer, const BitmapPart& part, const RectangleObject& source, Color tint) const
{
    Point2D topLeft = part.offset;
    Point2D topRight = part.offset;
    Point2D bottomLeft = part.offset;

    topRight.Translate(source.GetWidth(), 0);
    bottomLeft.Translate(0, source.GetHeight());

    renderer.DrawBitmap(part.bitmap, source, TransformPoint(topLeft), TransformPoint(topRight), TransformPoint(bottomLeft), tint);
}

void BitmapObject::Draw(PrimitiveRenderer& renderer) const
{
    for (const auto& part : bitmaps)
    {
        RectangleObject source(Point2D(0, 0), part.bitmap.getWidth(), part.bitmap.getHeight());

        DrawPart(renderer, part, source);
    }
}

void BitmapObject::Translate(float tx, float ty)
{
    position.Translate(tx, ty);
    axisX.Translate(tx, ty);
    axisY.Translate(tx, ty);
}

void BitmapObject::Rotate(float angle)
{
    position.Rotate(angle);
    axisX.Rotate(angle);
    axisY.Rotate(angle);
}

void BitmapObject::Rotate(float angle, const Point2D& origin)
{
    position.Rotate(angle, origin);
    axisX.Rotate(angle, origin);
    axisY.Rotate(angle, origin);
}

void BitmapObject::Scale(float kx, float ky)
{
    position.Scale(kx, ky);
    axisX.Scale(kx, ky);
    axisY.Scale(kx, ky);
}

void BitmapObject::Scale(float kx, float ky, const Point2D& origin)
{
    position.Scale(kx, ky, origin);
    axisX.Scale(kx, ky, origin);
    axisY.Scale(kx, ky, origin);
}