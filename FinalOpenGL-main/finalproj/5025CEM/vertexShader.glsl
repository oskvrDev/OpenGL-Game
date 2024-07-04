#version 430 core

#define FIELD 0
#define SKY 1
#define SPHERE 2
#define TABLE 3
//#define HOVER 4

layout(location=0) in vec4 Coords;
layout(location=1) in vec2 TexCoords;
layout(location=2) in vec4 sphereCoords;
layout(location=3) in vec3 sphereNormals;

layout(location=4) in vec3 objCoords;
layout(location=5) in vec3 objNormals;
layout(location=6) in vec2 objTexCoords;

uniform mat4 modelViewMat;
uniform mat4 projMat;
uniform uint object;
uniform float yPos;

out vec2 texCoordsExport;
out vec3 normalExport;

vec4 coords;

void main(void)
{   
   if (object == FIELD)
   {
      coords = Coords;
      texCoordsExport = TexCoords;
   }
   if (object == SKY)
   {
      coords = Coords;
      texCoordsExport = TexCoords;
   }
   if (object == SPHERE)
   {
      coords = sphereCoords;
      normalExport = sphereNormals;
   }

    if (object == TABLE)
    {
      coords = vec4(objCoords, 1.0f);
      coords.y = coords.y+yPos;
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }

    /*if (object == HOVER)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }*/
   
   gl_Position = projMat * modelViewMat * coords;
}
