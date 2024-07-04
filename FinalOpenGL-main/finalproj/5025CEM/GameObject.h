#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>
#include "Particle.h"
//#include "Model.h"
class GameObject
{

	public:
		GameObject();
		GameObject(glm::vec3);
		GameObject(float, glm::vec3);
		virtual ~GameObject();


		virtual void Draw() = 0;  // set it as pure virtual - can't instantiate, all children must heve thier own definition
		virtual void Update(float deltaTime);

		//maps for key input
		static std::map<char, bool> keys;
		static std::map<int, bool> specialKeys;
	
		glm::vec3 position;

		//OpenGL drawing function
		//virtual void Draw() = 0;

		//physics update function
		//virtual void Update(float);

		//keyboard input
		//static std::map<char, bool> keys;
		//static std::map<char, bool> specialKeys;

protected:
	Particle* particlePtr;
	//Model* modelPtr;
	


};

