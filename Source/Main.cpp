#include <ctime>
#include <iostream>

#include <Core/Engine.h>

#include "Files/Scene2D.h"

using namespace std;

#define WINDOW_WIDTH_PX		1280
#define WINDOW_HEIGHT_PX	720

int main(int argc, char **argv)
{
	
	WindowProperties wp;
	wp.resolution = glm::ivec2(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX);

	WindowObject* window = Engine::Init(wp);


	World *world = new Scene2D();
	world->Init();
	world->Run();

	Engine::Exit();

	return 0;
}