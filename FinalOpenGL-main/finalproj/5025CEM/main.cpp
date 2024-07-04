#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "RotatingSquare.h"

#pragma comment(lib, "glew32.lib") 

GameObject* player = new Player(1.0f, 1.0f, glm::vec3(0, 0, 0));
GameObject* rotatingCube = new RotatingSquare(1.f, 1.f,glm::vec3(0, 0, 0));

GameEngine engine;


int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "Pool Game", 500, 500);

	engine.AddGameObject(player);
	engine.AddGameObject(rotatingCube);

	engine.StartEngine();

	return 0;
}






