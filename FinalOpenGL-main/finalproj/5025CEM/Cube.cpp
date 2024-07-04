#include "Cube.h"

Cube::Cube(float, glm::vec3 position, float, float, float, float, const char*): GameObject(position)
{
	//pos = position;
}

Cube::~Cube()
{
}

void Cube::Draw()
{

	//modelPtr->Draw();


}

void Cube::Update(float deltaTime)
{
	particlePtr->ResetForces();
	particlePtr->AddForce(glm::vec3(0.0f, -1.0f, 0.0f) * particlePtr->GetMass()); // gravity


	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		particlePtr->AddForce(glm::vec3(0.0f, 0.0f, -1.0f));
		
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		particlePtr->AddForce(glm::vec3(0.0f, 0.0f, 1.0f));
		
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		particlePtr->AddForce(glm::vec3(1.0f, 0.0f, 0.0f));
		
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		particlePtr->AddForce(glm::vec3(-1.0f, 0.0f, 0.0f));
		
	particlePtr->Update(0.01f);
}