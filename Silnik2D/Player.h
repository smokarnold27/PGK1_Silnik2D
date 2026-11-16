#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"
#include "UpdatableObject.h"
#include "RectangleObject.h"
#include "Point2D.h"



class Player : public virtual GameObject
{
	public:
		Point2D pos; //POZYCJA GRACZA

		int speed = 2; //PREDKOSC/O ILE PIKSELI GRACZ PRZESUWA SIE PRZY POJEDYNCZYM RUCHU
		int size; //ROZMIAR GRACZA

		Player(Point2D pos, int size);

		void Draw(PrimitiveRenderer& renderer) const;
		void Translate(float tx, float ty);
		void Rotate(float angle);
		void Rotate(float angle, const Point2D& origin);
		void Scale(float kx, float ky);
		void Scale(float kx, float ky, const Point2D& origin);


};
