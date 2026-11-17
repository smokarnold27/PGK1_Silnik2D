#pragma once
#include "BitmapObject.h"
#include "AnimatedObject.h"

class SpriteObject : public BitmapObject, public AnimatedObject
{
protected:
    int frameCount;
    int currentFrame = 0;

    float frameDuration;
    float elapsedTime = 0.0f;

    bool playing = true;

public:
    SpriteObject(int frames, float fps = 10.0f);

    bool AddBitmap(const char* filename, const Point2D& offset = Point2D()) override;

    void animate() override;

    void Draw(PrimitiveRenderer& renderer) const override;

    void Play();
    void Pause();
    void Stop();

    void SetFPS(float fps);
    int GetCurrentFrame() const;
};