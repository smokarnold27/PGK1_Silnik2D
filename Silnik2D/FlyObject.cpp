#include "FlyObject.h"
#include "PrimitiveRenderer.h"
#include <cmath>

FlyObject::FlyObject(const Point2D& startPos, float speedX, float speedY)
    : SpriteObject(2, 8.0f), pos(startPos), vx(speedX), vy(speedY)
{
    BitmapObject::Translate(pos.GetExactX(), pos.GetExactY());
    AddBitmap("../Mucha.png");
}

void FlyObject::Update(float deltaTime)
{
    // Ruch w skos
    pos.Translate(vx * deltaTime, vy * deltaTime);
    BitmapObject::Translate(vx * deltaTime, vy * deltaTime);

    float x = pos.GetExactX();
    float y = pos.GetExactY();

    // Granice rzeki: X od 80 do 720 (szerokość muchy to 32, więc 720 - 32 = 688)
    if (x <= 80.0f) {
        x = 80.0f;
        vx = -vx;
    }
    else if (x >= 688.0f) {
        x = 688.0f;
        vx = -vx;
    }

    // Granice pionowe rzeki: Y od 12 do 588 (wysokość muchy 32, więc 588 - 32 = 556)
    if (y <= 12.0f) {
        y = 12.0f;
        vy = -vy;
    }
    else if (y >= 556.0f) {
        y = 556.0f;
        vy = -vy;
    }

    pos = Point2D(x, y);

    // Obliczanie kąta rotacji na podstawie kierunku ruchu (wektora prędkości vx, vy)
    // Dodajemy PI / 2 (90 stopni), ponieważ domyślna grafika muchy patrzy w górę (0, -1)
    if (vx != 0.0f || vy != 0.0f) {
        currentAngle = std::atan2(vy, vx) + (PI / 2.0f);
    }

    Play();
    animate();
}

void FlyObject::Draw(PrimitiveRenderer& renderer) const
{
    if (!bitmaps.empty()) {
        const auto& part = bitmaps[0];
        int frameWidth = part.bitmap.getWidth() / frameCount; // 32
        int frameHeight = part.bitmap.getHeight(); // 32
        RectangleObject source(Point2D(static_cast<float>(currentFrame * frameWidth), 0.0f), static_cast<float>(frameWidth), static_cast<float>(frameHeight));

        // Środek muchy
        float cx = pos.GetExactX() + frameWidth / 2.0f;
        float cy = pos.GetExactY() + frameHeight / 2.0f;

        float cosA = std::cos(currentAngle);
        float sinA = std::sin(currentAngle);

        float halfW = frameWidth / 2.0f;
        float halfH = frameHeight / 2.0f;

        // Lambda do obracania lokalnych rogów [-16, 16] wokół środka muchy (cx, cy)
        auto rotatePoint = [cx, cy, cosA, sinA](float lx, float ly) {
            return Point2D(cx + lx * cosA - ly * sinA, cy + lx * sinA + ly * cosA);
            };

        // Wyznaczenie obróconych narożników dla PrimitiveRenderer::DrawBitmap
        Point2D topLeft = rotatePoint(-halfW, -halfH);
        Point2D topRight = rotatePoint(halfW, -halfH);
        Point2D bottomLeft = rotatePoint(-halfW, halfH);

        renderer.DrawBitmap(part.bitmap, source, topLeft, topRight, bottomLeft);
    }
}