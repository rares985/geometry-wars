#include <ctime>
#include <iostream>

#include <Core/Engine.h>

#include "Files/Scene2D.h"
#include "Files/constants.h"

using namespace std;

int main(int argc, char **argv)
{

	/* Seed the RNG */
	srand((unsigned int)time(NULL));
	
	WindowProperties wp;
	wp.resolution = glm::ivec2(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX);

	WindowObject* window = Engine::Init(wp);
	window->SetVSync(true);

	std::unique_ptr<World> world(new Scene2D());

	world->Init();
	world->Run();

	Engine::Exit();

	return 0;
}