#include "GameEngine.h"

vector<GameObject*> GameEngine::objects;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;


static enum object { FIELD, SKY, SPHERE, TABLE }; // VAO ids.
static enum buffer { FIELD_VERTICES, SKY_VERTICES, SPHERE_VERTICES, SPHERE_INDICES, TABLE_VERTICES }; // VBO ids.

//Camera GameEngine::camera;
//glm::vec3 GameEngine::cameraLocation = glm::vec3(0, 0, 0);

static Vertex fieldVertices[] = {

    {vec4(100.0, 0.0, 100.0, 1.0), vec2(8.0, 0.0)},
    {vec4(100.0, 0.0, -100.0, 1.0), vec2(8.0, 8.0)},
    {vec4(-100.0, 0.0, 100.0, 1.0), vec2(0.0, 0.0)},
    {vec4(-100.0, 0.0, -100.0, 1.0), vec2(0.0, 8.0)}

};

static Vertex skyVertices[] = {

    {vec4(100.0, 0.0, -70.0, 1.0), vec2(1.0, 0.0)},
    {vec4(100.0, 120.0, -70.0, 1.0), vec2(1.0, 1.0)},
    {vec4(-100.0, 0.0, -70.0, 1.0), vec2(0.0, 0.0)},
    {vec4(-100.0, 120.0, -70.0, 1.0), vec2(0.0, 1.0)}
};

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

static mat4 modelViewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);  //create normal matrix

static const vec4 globAmb = vec4(0.2, 0.2, 0.2, 1.0);
// Front and back material properties.
static const Material sphereFandB =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	50.0f
};

static const Light light0 =
{
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 0.0)
};

static unsigned int
programId,
vertexShaderId,
fragmentShaderId,
modelViewMatLoc,
projMatLoc,
modelMatLoc,
viewMatLoc,
objectLoc,
grassTexLoc,  //for grass texture 
skyTexLoc,
woodTexLoc,
buffer[6],    //VBO List
vao[5],	     //VAO List
texture[3];   //Texture List

std::vector<GameEngine*> objects;
float zVal = 0; // Z Co-ordinates of the ball.
float d = 0.0; //Camera position
static Model table("tabletop2.obj");
static Sphere testSphere;

void GameEngine::StartEngine(void)
{
	std::cout << "Press escape to exit the game." << std::endl;
	glutMainLoop();
}

void GameEngine::UpdateGame(void) {

	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	deltaTime /= 1000.f;

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	glutPostRedisplay();
}

void GameEngine::Setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Create shader program executable.
	vertexShaderId = setShader("vertex", "vertexShader.glsl");
	fragmentShaderId = setShader("fragment", "fragmentShader.glsl");
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);

	//codes for OpenGL lighting
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.ambRefl"), 1, &sphereFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.difRefl"), 1, &sphereFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.specRefl"), 1, &sphereFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.emitCols"), 1, &sphereFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(programId, "sphereFandB.shininess"), sphereFandB.shininess);

	glUniform4fv(glGetUniformLocation(programId, "globAmb"), 1, &globAmb[0]);

	glUniform4fv(glGetUniformLocation(programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.specCols"), 1, &light0.specCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.coords"), 1, &light0.coords[0]);



	///// Create a Sky /////////////

	//Create VAO and VBO
	glGenVertexArrays(1, &vao[SKY]);
	glGenBuffers(1, &buffer[SKY_VERTICES]);
	glBindVertexArray(vao[SKY]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[SKY_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);  //layout(location=2) in vec4 skyCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords))); //layout(location=3) in vec2 skyTexCoords;
	glEnableVertexAttribArray(1);

	/////Create a sphere /////  

	glGenVertexArrays(1, &vao[SPHERE]);
	glGenBuffers(1, &buffer[SPHERE_VERTICES]);


	glGenVertexArrays(1, &vao[TABLE]);
	glGenBuffers(1, &buffer[TABLE_VERTICES]);

	//Binding VAO and VBO
	testSphere.SetIDs(vao[SPHERE], buffer[SPHERE_VERTICES], buffer[SPHERE_INDICES]);
	testSphere.Setup();


	//Binding Track VAO and VBO
	table.SetIDs(vao[TABLE], buffer[TABLE_VERTICES], 0);
	table.Setup();


	// Obtain projection matrix uniform location and set value.
	projMatLoc = glGetUniformLocation(programId, "projMat");   //uniform mat4 projMat;
	projMat = frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0); /*perspective(radians(60.0), 1.0, 0.1, 1000.0); *///
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));


	// Obtain modelview matrix uniform and object uniform locations.
	modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");   //uniform mat4 modelViewMat;
	objectLoc = glGetUniformLocation(programId, "object");  //uniform uint object;


	/*grassTexLoc = glGetUniformLocation(programId, "grassTex");
	woodTexLoc = glGetUniformLocation(programId, "woodTex");*/


	// Load the images.
	std::string TexNames[] = {
		 "Textures/grass.bmp",
		 "Textures/sky.bmp",
		 "Textures/wood.jpg"
		 "Textures/top.jpg",
	};

	// Create texture ids.
	glGenTextures(3, texture);

	int width, height;
	unsigned char* data;

	// Bind grass image.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//load image data using SOIL library
	data = SOIL_load_image(TexNames[0].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	grassTexLoc = glGetUniformLocation(programId, "grassTex");
	glUniform1i(grassTexLoc, 0); //send texture to shader

	//next texture

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	data = SOIL_load_image(TexNames[1].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	skyTexLoc = glGetUniformLocation(programId, "skyTex");
	glUniform1i(skyTexLoc, 1); //send texture to shader


	//NEXT TEXTURE

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	data = SOIL_load_image(TexNames[2].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	SOIL_free_image_data(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	woodTexLoc = glGetUniformLocation(programId, "woodTex");
	glUniform1i(woodTexLoc, 2); //send texture to shader

}

void GameEngine::DrawGame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate and update modelview matrix.
	modelViewMat = mat4(1.0);
	modelViewMat = lookAt(vec3(0.0, 10.0, 15.0), vec3(0.0 + d, 10.0, 0.0), vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, value_ptr(modelViewMat));

	// Draw field.
	glUniform1ui(objectLoc, FIELD);  //if (object == FIELD)
	glBindVertexArray(vao[FIELD]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Draw sky.
	glUniform1ui(objectLoc, SKY);  //if (object == SKY)
	glBindVertexArray(vao[SKY]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Draw sphere
	testSphere.updateModelMatrix(modelViewMatLoc, d);
	glUniform1ui(objectLoc, SPHERE);  //if (object == SPHERE)
	testSphere.Draw();

	//draw table
	vec3 pos = vec3(0.0, -0.3f, 0.0f);
	table.updateModelMatrix(modelViewMatLoc, d, 7.0f, pos);
	glUniform1ui(objectLoc, TABLE);  //if (object == MYMODEL)
	table.Draw();

	glutSwapBuffers();
}


void GameEngine::CleanupEngine(void)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}
}

void GameEngine::AddGameObject(GameObject* object)
{
    objects.push_back(object);
}

void GameEngine::ResizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{
    glutInit(&argc, argv);

    glutInitContextVersion(2, 0);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);
    glutDisplayFunc(DrawGame);
    glutReshapeFunc(ResizeWindow);
    glutIdleFunc(UpdateGame);
    glewExperimental = GL_TRUE;
    glewInit();
    glutKeyboardFunc([](unsigned char key, int x, int y)
        {
            GameObject::keys[key] = true;
            //std::cout << "Key pressed: " << key << " : " << GameObject::keys[key] << std::endl;
            //If we press escape, quit
            if (key == 27)
            {
                CleanupEngine();
                exit(0);
            }


            for (int i = 0; i < objects.size(); ++i)
            {
                delete objects[i];
            }
        }
    );
    glutKeyboardUpFunc([](unsigned char key, int x, int y)
        {
            GameObject::specialKeys[key] = false;
            std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
        }
    );
    glutSpecialFunc([](int key, int x, int y)
        {
            GameObject::specialKeys[key] = true;
            std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
        }
    );
    glutSpecialUpFunc([](int key, int x, int y)
        {
            GameObject::specialKeys[key] = false;
            std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
        }
    );
	glewExperimental = GL_TRUE;
	glewInit();

	GameEngine::Setup();
}