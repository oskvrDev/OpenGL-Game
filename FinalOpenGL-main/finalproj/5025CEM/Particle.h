#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>


class Particle
{
public:
	glm::vec3 position;


	void Update(float);
	Particle(float, glm::vec3);
	~Particle();
	void ResetForces();
	void AddForce(glm::vec3);
	float GetMass();
	glm::vec3 GetVelocity();
private:
	float mass;
	glm::vec3 velocity, forceOnObj, acceleration;







};

