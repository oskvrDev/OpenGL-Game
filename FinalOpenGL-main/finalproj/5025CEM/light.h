#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
using namespace glm;

struct Material
{
	vec4 ambRefl;
	vec4 difRefl;
	vec4 specRefl;
	vec4 emitCols;
	float shininess;
};

struct Light
{
	vec4 ambCols;
	vec4 difCols;
	vec4 specCols;
	vec4 coords;
};
