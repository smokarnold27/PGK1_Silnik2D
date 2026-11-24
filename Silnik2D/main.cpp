#include "Engine.h"

int main()
{
	Engine& engine = Engine::GetInstance(); // Pobranie instancji silnika (referencji do jedynego obiektu klasy Engine (singleton))
	if (engine.Init(800, 600, false, 60)) {
		engine.Run();
	}
	engine.Shutdown();
	return 0;
}