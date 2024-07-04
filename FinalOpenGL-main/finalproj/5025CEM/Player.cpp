#include "Player.h"
#include "Particle.h"


Player::Player(float s, float m, glm::vec3 pos) :GameObject(1.0f, pos)
{
	speed = s;
	mass = m;
	position = pos;
}

void Player::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f);
	glTranslatef( particlePtr->position.x, particlePtr->position.y, particlePtr->position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();

	glColor3f(1.f, 1.f, 1.f);
	glm::vec3 vel = particlePtr->GetVelocity();
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0); //0, 0, 0 is used here as I assume you have a glTranslatef line above, so 0, 0, 0 puts us at the center of the object now
	glVertex3f(vel.x, vel.y, vel.z);
	glEnd();
}




/*
The Update() function will run every frame so we will check for keyboard controls in this. The overall logic for Player's Update() will be as follows:

Reset the particle instance inside Player's total force to zero.

Check for key presses. If the use presses the arrow keys, add a force (one of the axis directions for each key press) to the total force variable.

Make sure this force includes the speed variable of Player, allowing different speeds to affect the force amount added

Update the particle instance as normal, which integrates to work out the acceleration, then velocity, then position
*/

void Player::input()
{
	

	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		particlePtr->AddForce(glm::vec3(0.f, 0.f, -1.f));
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		particlePtr->AddForce(glm::vec3(0.f, 0.f, 1.f));
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		particlePtr->AddForce(glm::vec3(1.f, 0.f, 0.f));
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		particlePtr->AddForce(glm::vec3(-1.f, 0.f, 0.f));

	
}

void Player::Update(float deltaTime)
{
	input();
	particlePtr->Update(deltaTime);
}

Player::~Player()
{
}
