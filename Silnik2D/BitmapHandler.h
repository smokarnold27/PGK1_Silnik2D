#pragma once
#include "raylib.h"

class BitmapHandler
{
private:
    Image bitmap;

public:
    BitmapHandler();
    ~BitmapHandler();

    BitmapHandler(const BitmapHandler& other);

    BitmapHandler& operator=(const BitmapHandler& other);

    bool create(int width, int height, Color color = WHITE);
    void remove();

    bool load(const char* filename);
    bool save(const char* filename) const;

    void copy(const BitmapHandler& other);

    int getWidth() const;
    int getHeight() const;
    Color getPixel(int x, int y) const;
    bool isValid() const;

    Texture2D createTexture() const;

};