#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "soil/SOIL.h"

#include "shader.h"
#include "vertex.h"
#include "sphere.h"
#include "Model.h"
#include "GameObject.h"
#include "Particle.h"
#include "Player.h"
#include "Cube.h"
#include "Sphere.h"
#include "RotatingSquare.h"
#include <vector>
#include <glm/gtx/string_cast.hpp>

#pragma comment(lib, "glew32.lib") 
#endif



using namespace std;
using namespace glm;


class GameEngine {


public:

	int width;
	int height;
	void InitEngine(int, char**, const char*, int width , int height);
	void AddGameObject(GameObject*);
	void StartEngine();
	static void Setup();
	GameObject* player = new Player(1.0f, 1.0f, glm::vec3(0, 0, 0));

private:

	static vector<GameObject*> objects;
	static int oldTimeSinceStart;
	static int newTimeSinceStart;

	static void UpdateGame(void);
	static void DrawGame(void);
	static void CleanupEngine();
    static void ResizeWindow(int width, int height);
	
	


};
