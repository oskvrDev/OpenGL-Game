#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "RigidBody2D.h"


class RotatingSquare : public GameObject
{
public:
	float speed;
	void Draw();
	void Update(float deltaTime) override;
	RotatingSquare(float _mass,float _speed, glm::vec3 _position) :GameObject(_position) 
	{
		rigidbodyPtr = new RigidBody2D(_position, _mass);
		speed = _speed;
	} //(that takes a mass, a speed and position value)
	~RotatingSquare();

protected:
	RigidBody2D* rigidbodyPtr;
};

