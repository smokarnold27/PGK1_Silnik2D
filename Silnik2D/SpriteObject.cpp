#include "SpriteObject.h"
#include "PrimitiveRenderer.h"
#include <cmath>

SpriteObject::SpriteObject(int frames, float fps)
{
    frameCount = (frames > 0) ? frames : 1;

    frameDuration = 0.1f;

    SetFPS(fps);
}

bool SpriteObject::AddBitmap(const char* filename, const Point2D& offset)
{
    BitmapPart part;

    if (!part.bitmap.load(filename))
        return false;

    // Kazdy arkusz musi miec odpowiednia liczbe klatek o jednakowej szerokosci
    if (part.bitmap.getWidth() % frameCount != 0)
        return false;

    part.offset = offset;

    bitmaps.push_back(part);

    return true;
}

void SpriteObject::animate()
{
    if (!playing)
        return;

    elapsedTime += GetFrameTime();

    while (elapsedTime >= frameDuration)
    {
        elapsedTime -= frameDuration;

        currentFrame = (currentFrame + 1)
            % frameCount;
    }
}

void SpriteObject::Draw(PrimitiveRenderer& renderer) const
{
    for (const auto& part : bitmaps)
    {
        int frameWidth = part.bitmap.getWidth() / frameCount;

        int frameHeight = part.bitmap.getHeight();

        RectangleObject source(Point2D(currentFrame * frameWidth, 0), frameWidth, frameHeight);

        DrawPart(renderer, part, source);
    }
}

void SpriteObject::Play()
{
    playing = true;
}

void SpriteObject::Pause()
{
    playing = false;
}

void SpriteObject::Stop()
{
    playing = false;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void SpriteObject::SetFPS(float fps)
{
    if (fps > 0.0f && std::isfinite(fps))
    {
        frameDuration = 1.0f / fps;
        elapsedTime = 0.0f;
    }
}

int SpriteObject::GetCurrentFrame() const
{
    return currentFrame;
}