#include "Player.h"
#include "PrimitiveRenderer.h"
#include <algorithm>

Player::Player(const Point2D& pos, int size, Color color, int speed) : SpriteObject(3, 8.0f) {
	this->pos = pos;
	this->size = size;
	this->color = color;
	this->speed = speed;

	BitmapObject::Translate(pos.GetExactX(), pos.GetExactY());
	AddBitmap("../ZabaPrzod.png");
	AddBitmap("../ZabaTyl.png");
	AddBitmap("../ZabaPrawo.png");
	AddBitmap("../ZabaLewo.png");
	BitmapObject::Scale(2.0f, 2.0f, pos);
}

void Player::Draw(PrimitiveRenderer& renderer) const
{
	if (kierunek >= 0 && static_cast<size_t>(kierunek) < bitmaps.size()) {
		const auto& part = bitmaps[kierunek];
		int frameWidth = part.bitmap.getWidth() / frameCount;
		int frameHeight = part.bitmap.getHeight();
		RectangleObject source(Point2D(currentFrame * frameWidth, 0), frameWidth, frameHeight);
		DrawPart(renderer, part, source);
	}
	else {
		renderer.DrawFilledRectangle(pos, size, size, color);
	}
}

void Player::Update(float deltaTime)
{
	bool ruch = false;
	//STEROWANIE GRACZEM
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
		Translate(1, 0);
		kierunek = 2;
		ruch = true;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
		Translate(-1, 0);
		kierunek = 3;
		ruch = true;
	}
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
		Translate(0, -1);
		kierunek = 1;
		ruch = true;
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
		Translate(0, 1);
		kierunek = 0;
		ruch = true;
	}

	if (ruch) {
		Play();
		animate();
	}
	else {
		Stop();
	}
}

void Player::Translate(float tx, float ty)
{
	pos.Translate(tx * speed, ty * speed);
	BitmapObject::Translate(tx * speed, ty * speed);
}

void Player::Rotate(float angle)
{
	pos.Rotate(angle);
	BitmapObject::Rotate(angle);
}

void Player::Rotate(float angle, const Point2D& origin)
{
	pos.Rotate(angle, origin);
	BitmapObject::Rotate(angle, origin);
}

void Player::Scale(float kx, float ky)
{
	size = static_cast<int>(size * std::abs(kx));
	pos.Scale(kx, ky);
	BitmapObject::Scale(kx, ky);
}

void Player::Scale(float kx, float ky, const Point2D& origin)
{
	size = static_cast<int>(size * std::abs(kx));
	pos.Scale(kx, ky, origin);
	BitmapObject::Scale(kx, ky, origin);
}