#include <iostream>
#include "Engine.h"
#include "raylib.h"

using namespace std;



int main()
{
	float time = 0.0f;
	Engine engine;
	engine.Inicjuj(800, 600, false, 60);

	return 0;
}