#pragma once
#include "SpriteObject.h"
#include "UpdatableObject.h"
#include "Point2D.h"
#include "raylib.h"

class FlyObject : public SpriteObject, public UpdatableObject
{
private:
    Point2D pos;
    float vx;
    float vy;
    float currentAngle = 0.0f; // Kąt rotacji w radianach

public:
    FlyObject(const Point2D& startPos, float speedX, float speedY);

    void Update(float deltaTime) override;
    void Draw(class PrimitiveRenderer& renderer) const override;

    Point2D GetPosition() const { return pos; }
    int GetSize() const { return 32; }
};