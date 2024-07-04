#include "RotatingSquare.h"
#include <iostream>

void RotatingSquare::Draw()
{
    glPushMatrix(); //dont affect other objects, only this one so take a copy of the matrix and put it on the stack
    glTranslatef(rigidbodyPtr->position.x, rigidbodyPtr->position.y, rigidbodyPtr->position.z); //then this happens
    glRotatef(glm::degrees(rigidbodyPtr->orientation.z), 0, 0, 1); //this really happens first
    glColor3f(0.f, 0.f, 1.f);

    float squareLength = 1.0f;
    float squareWidth = 1.0f;

    glBegin(GL_QUADS);
    glVertex3f(-squareLength, squareWidth, 0); //top left
    glVertex3f(squareLength, squareWidth, 0); //top right
    glVertex3f(squareLength, -squareWidth, 0); //bottom right
    glVertex3f(-squareLength, -squareWidth, 0); //bottom left
    glEnd();

    glPointSize(5.0f); // so we can see the point better

    glColor3f(0.f, 0.f, 0.f);
    glBegin(GL_POINTS);
    //at the middle of object
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix(); //forget about what we've done to this object so push off the stack - we are back to before the glPushMatrix() happened
}

void RotatingSquare::Update(float deltaTime)
{
    /*
    Make sure this force includes the speed variable of RotatingSquare, allowing different speeds to affect the force amount added
    */
    rigidbodyPtr->ResetForces();


	if (GameObject::specialKeys[GLUT_KEY_UP] == true) 
	{
		rigidbodyPtr->AddAngularForce(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f) * speed);
	}

	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true) 
	{
		rigidbodyPtr->AddAngularForce(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f) * speed);
	}

	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
	{
		rigidbodyPtr->AddAngularForce(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.0f) * speed);
	}

	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
	{
		rigidbodyPtr->AddAngularForce(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f) * speed);
	}

    rigidbodyPtr->Update(0.01f);

}


RotatingSquare::~RotatingSquare()
{
	delete rigidbodyPtr;
}
