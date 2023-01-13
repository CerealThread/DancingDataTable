#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Plane.h"
#include "Field.h"
#include "FieldController.h"
#include "FastNoiseLite.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/constants.hpp>


unsigned int width = 1000;
unsigned int height = 800;

FieldController controller1(width, height, 20, 10);
FieldController controller2(width, height, 20, 10);
FieldController controller3(width, height, 20, 10);

FieldController controllers[] = {controller1, controller2, controller3};
unsigned int ActiveController = 1;



string csvFileNames[] = {"resources/test.csv", "resources/test2.csv", "resources/Education_data_table.csv"};

float x,y;

const float PI = glm::pi<float>();

int lastX = width/2;
int lastY = height/2;

int curX = lastX;
int curY = lastY;

float lastTime = glutGet(GLUT_ELAPSED_TIME);
float deltaTime = 0.0;


const float MOVE_SPEED = 1.0f;
const float MOUSE_SENSITIVITY = 0.1f;


void Init(void);
void Display(void);
void Finalize(void);
void Idle();
void move();
void Keyboard(unsigned char, int x, int y);
void mouseMove(int mouseX, int mouseY);

void Init(void)
{
	
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);

    glutCreateWindow("Test");
    glewExperimental = GL_TRUE;
    if (glewInit()) {
        printf("Unable to initialize GLEW ... exiting\n");
    }
	
	glEnable(GL_DEPTH_TEST);

	glutSetCursor(GLUT_CURSOR_NONE);

	


	std::vector<glm::vec3> instances;


	for(int i = 0; i < sizeof(controllers)/sizeof(controllers[0]); i++) {
		controllers[i].loadShaders();
		controllers[i].makeFields(csvFileNames[i]);
	}


	glutIgnoreKeyRepeat(false);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - lastTime;

	int sizeX = 10;
    int sizeZ = 10;
    float lengthX = 2.0f;
    float lengthZ = 2.0f;


	controllers[ActiveController].DrawFields();


	lastTime = currentTime;

	glutSwapBuffers();	
}

void move(int value)
{
	controllers[ActiveController].genOffsetInstances();
	
	glutPostRedisplay();
	glutTimerFunc(25, move, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
		case 27:
			exit(0);
		case 97:
			ActiveController = (ActiveController + 1) % (sizeof(controllers)/sizeof(controllers[0]));
	}
	
}

void ChangeCam(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_RIGHT:
			controllers[ActiveController].setNextCam();
	}
}

void Idle()
{
	glutPostRedisplay();
}

void Finalize(void)
{

}

void mouseMove(int x, int y) 
{
	int deltaX = x - lastX;
	int deltaY = y - lastY;



	lastX = x;
	lastY = y;


	if(deltaX == 0 && deltaY == 0) return;

	if(x >= width-10 || x <= 10 || y >= height-10 || y < 10)
	{
		lastX = width/2;
		lastY = height/2;

		deltaX = 0;
		deltaY = 0;

		glutWarpPointer(width/2, height/2);
	}


	curX += deltaX;
	curY += deltaY;

	for(int i = 0; i < sizeof(controllers)/sizeof(controllers[0]); i++) {
		controllers[i].rotateCamera((float)(deltaX) * MOUSE_SENSITIVITY, (float)(deltaY) * MOUSE_SENSITIVITY);
	}
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    Init();
	
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(ChangeCam);
	glutTimerFunc(25, move, 1);
	glutPassiveMotionFunc(mouseMove);
	glutMainLoop();
	
	return 0;	
}
int mouseY = 0;
