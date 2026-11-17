#include "Player.h"
#include "PrimitiveRenderer.h"
#include <algorithm>

Player::Player(const Point2D& pos, int size, Color color, int speed) {
	this->pos = pos;
	this->size = size;
	this->color = color;
	this->speed = speed;
}

void Player::Draw(PrimitiveRenderer& renderer) const
{
	renderer.DrawFilledRectangle(pos, size, size, color);
}

void Player::Update(float deltaTime)
{
	//STEROWANIE GRACZEM
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
		Translate(1, 0);
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
		Translate(-1, 0);
	}
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
		Translate(0, -1);
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
		Translate(0, 1);
	}
}

void Player::Translate(float tx, float ty)
{
	pos.Translate(tx * speed, ty * speed);
}

void Player::Rotate(float angle)
{
	pos.Rotate(angle);
}

void Player::Rotate(float angle, const Point2D& origin)
{
	pos.Rotate(angle, origin);
}

void Player::Scale(float kx, float ky)
{
	size = static_cast<int>(size * std::abs(kx));
	pos.Scale(kx, ky);
}

void Player::Scale(float kx, float ky, const Point2D& origin)
{
	size = static_cast<int>(size * std::abs(kx));
	pos.Scale(kx, ky, origin);
}