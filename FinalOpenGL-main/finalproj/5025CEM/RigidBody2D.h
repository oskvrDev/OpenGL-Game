#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
class RigidBody2D
{
public:

	float mass;
	float inertia;
//	float drag; // slow down forc
	glm::vec3 orientation;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 forceOnObj, acceleration;
	glm::vec3 totalAngularForce;
	glm::vec3 angularVelocity, angularAcceleration;

	void Update(float);
	void ResetForces();
	void AddForce(glm::vec3);
	void AddAngularForce(glm::vec3, glm::vec3);
	RigidBody2D(glm::vec3, float);	// mass, position, center of mass? rotation 0 by def	
	~RigidBody2D();





};

