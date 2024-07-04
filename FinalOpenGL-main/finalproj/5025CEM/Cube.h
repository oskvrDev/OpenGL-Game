#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
class Cube : public GameObject
{

public:
	Cube(float, glm::vec3 position, float, float , float , float , const char*);
	~Cube();


	void Draw();
	void Update(float deltaTime);
private:




};

