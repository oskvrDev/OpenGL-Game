#include "RigidBody2D.h"

void RigidBody2D::Update(float deltaTime)
{
	/*
	Reset the forces and angular forces/moments to zero
	Identify and quantify all forces and moments currently acting on the rigid body
	Take vector sum for linear and angular movement
	Solve equations of motion for linear and angular accelerations
	Integrate with respect to time to find the linear and angular velocities
	Integrate again to find the linear and angular displacements
	Position and orientation respectively
	*/
	// calculations from linear motion
	acceleration = forceOnObj / mass;
	position = position + (velocity * deltaTime);
	velocity = velocity + (acceleration * deltaTime);

	velocity *= pow(0.5f, deltaTime);


	// -------Angular force calculations-------
	//  This should reset the classes total angular force variable
	//	Add the needed integrator method for rotational motion
	//	Dampen the angular velocity so that the object slows down over time
	// Torque = force x distance from the force and pivot point  (cross product)
	angularAcceleration = totalAngularForce / inertia;
	orientation = orientation + (angularVelocity * deltaTime);
	angularVelocity = angularVelocity + (angularAcceleration * deltaTime);

	angularVelocity *= pow(0.5f, deltaTime);


}

void RigidBody2D::ResetForces()
{
	forceOnObj = glm::vec3(0, 0, 0);
	totalAngularForce = glm::vec3(0, 0, 0);
}


void RigidBody2D::AddForce(glm::vec3 force)
{
	forceOnObj += force;
}

void RigidBody2D::AddAngularForce(glm::vec3 force, glm::vec3 position)
{
	//forcePosition = position;
	forceOnObj += force;
	totalAngularForce += glm::cross( force, position); // force
}



RigidBody2D::RigidBody2D(glm::vec3 _position, float _mass)
{
	position = _position;
	mass = _mass;

	acceleration = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	forceOnObj = glm::vec3(0, 0, 0);
	totalAngularForce = glm::vec3(0, 0, 0);
	angularVelocity = glm::vec3(0, 0, 0);
	angularAcceleration = glm::vec3(0, 0, 0);

	inertia = 0.2f;

}

RigidBody2D::~RigidBody2D()
{
}
