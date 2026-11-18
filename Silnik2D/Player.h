#pragma once
#include "SpriteObject.h"
#include "UpdatableObject.h"
#include "Point2D.h"
#include "raylib.h"

class Player : public SpriteObject, public UpdatableObject
{
private:
	Point2D pos; //POZYCJA GRACZA
	int speed; //PREDKOSC/O ILE PIKSELI GRACZ PRZESUWA SIE PRZY POJEDYNCZYM RUCHU
	int size; //ROZMIAR GRACZA
	Color color; //KOLOR GRACZA
	int kierunek = 0; // 0-przod, 1-tyl, 2-prawo, 3-lewo

public:

	Player(const Point2D& pos, int size, Color color = BLACK, int speed = 2);

	Point2D GetPosition() const { return pos; }
	void SetPosition(const Point2D& pos) { this->pos = pos; }

	void Draw(class PrimitiveRenderer& renderer) const override;

	void Update(float deltaTime) override;

	void Translate(float tx, float ty) override;
	void Rotate(float angle) override;
	void Rotate(float angle, const Point2D& origin) override;
	void Scale(float kx, float ky) override;
	void Scale(float kx, float ky, const Point2D& origin) override;
};