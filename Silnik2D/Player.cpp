#include "Player.h"
#include "PrimitiveRenderer.h"



Player::Player(Point2D pos, int size)
{
	this->pos = pos;
	this->size = size;
}

//GRACZ JEST NARAZIE FIOLETOWYM KWADRATEM
void Player::Draw(PrimitiveRenderer& renderer) const
{
	renderer.DrawFilledRectangle(pos, size, size, PURPLE);

}

void Player::Translate(float tx, float ty)
{
	pos.Translate(tx*speed, ty*speed);
}

