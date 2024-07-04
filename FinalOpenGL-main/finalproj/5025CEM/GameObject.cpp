#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

void GameObject::Update(float deltaTime)
{
	
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		particlePtr->position.z -= 1.5f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		particlePtr->position.z += 1.5f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		particlePtr->position.x += 1.5f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		particlePtr->position.x -= 1.5f * deltaTime;
}



GameObject::GameObject()
{
	//pos = glm::vec3(0, 0, 0);
	particlePtr = new Particle(1.f, glm::vec3(0.f, 0.f, 0.f));
}

GameObject::GameObject(glm::vec3 _position)
{
	//pos = pos;
	particlePtr = new Particle(1.f, _position);
}

GameObject::GameObject(float _mass, glm::vec3 _position)
{
	particlePtr = new Particle(_mass, _position);
}


GameObject::~GameObject()
{
	delete particlePtr;
}


