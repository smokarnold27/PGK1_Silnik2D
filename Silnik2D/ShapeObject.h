#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "DrawableObject.h"
#include "TransformableObject.h"

class ShapeObject :
    public DrawableObject,
    public TransformableObject
{
	virtual ~ShapeObject() = default; // Wirtualny destruktor, aby umożliwić poprawne usuwanie obiektów pochodnych przez wskaźnik do klasy bazowej
};

