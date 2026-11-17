#include "BitmapHandler.h"



// Konstruktor
BitmapHandler::BitmapHandler()
{
    bitmap = Image{};
}

// Destruktor
BitmapHandler::~BitmapHandler()
{
    remove();
}

BitmapHandler::BitmapHandler(const BitmapHandler& other)
{
    bitmap = {};

    if (other.isValid())
    {
        bitmap = ImageCopy(other.bitmap);
    }
}

BitmapHandler& BitmapHandler::operator=(const BitmapHandler& other)
{
    if (this != &other)
    {
        Image newBitmap = {};

        if (other.isValid())
        {
            newBitmap = ImageCopy(other.bitmap);
        }

        remove();

        bitmap = newBitmap;
    }

    return *this;
}

// Tworzenie bitmapy
bool BitmapHandler::create(int width, int height, Color color)
{
    if (width <= 0 || height <= 0)
        return false;

    remove();

    bitmap = GenImageColor(width, height, color);

    return isValid();
}

// Usuwanie bitmapy
void BitmapHandler::remove()
{
    if (bitmap.data != nullptr)
    {
        UnloadImage(bitmap);
    }

    bitmap = {};
}

// Wczytywanie bitmapy z pliku
bool BitmapHandler::load(const char* filename)
{
    Image loaded = LoadImage(filename);

    if (loaded.data == nullptr)
        return false;

    remove();
    bitmap = loaded;

    return true;
}

// Zapisywanie bitmapy do pliku
bool BitmapHandler::save(const char* filename) const
{
    if (!isValid())
        return false;

    return ExportImage(bitmap, filename);
}

// Kopiowanie bitmapy
void BitmapHandler::copy(const BitmapHandler& other)
{
    if (this == &other)
        return;

    remove();

    if (other.isValid())
    {
        bitmap = ImageCopy(other.bitmap);
    }
}

// Pobieranie szerokości
int BitmapHandler::getWidth() const
{
    return bitmap.width;
}

// Pobieranie wysokości
int BitmapHandler::getHeight() const
{
    return bitmap.height;
}

Color BitmapHandler::getPixel(int x, int y) const
{
    if (isValid() && x >= 0 && y >= 0 &&
        x < bitmap.width && y < bitmap.height)
    {
        return GetImageColor(bitmap, x, y);
    }

    return BLANK;
}


bool BitmapHandler::isValid() const
{
    return bitmap.data != nullptr &&
        bitmap.width > 0 &&
        bitmap.height > 0;
}

// Tworzenie tekstury umożliwiającej wyświetlenie
Texture2D BitmapHandler::createTexture() const
{
    if (isValid())
    {
        return LoadTextureFromImage(bitmap);
    }

    return Texture2D{};
}