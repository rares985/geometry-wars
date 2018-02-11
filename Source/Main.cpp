#include <ctime>
#include <iostream>

#include <Core/Engine.h>

#include "Files/Scene2D.h"

using namespace std;


int main(int argc, char **argv)
{
	
	WindowProperties wp;
	wp.resolution = glm::ivec2(1280, 720);

	WindowObject* window = Engine::Init(wp);


	World *world = new Scene2D();
	world->Init();
	world->Run();

	Engine::Exit();

	return 0;
}