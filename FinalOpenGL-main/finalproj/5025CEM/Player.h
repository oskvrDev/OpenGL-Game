#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
class Player : public GameObject
{
public:
	
	void Draw();
	void Update(float);
	void input();
	Player(float, float, glm::vec3);
	~Player();
	
	

private:

	float speed;
	float mass;
	glm::vec3 position;

		//Constructor(that takes a mass, a speed and position value)
		//- this should call the GameObject constructor, filling those bits of data too




};

