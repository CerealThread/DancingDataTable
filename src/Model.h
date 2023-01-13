#ifndef MODEL_H
#define MODEL_H


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include "Shader.h"
#include <vector>
#include <iostream>


using namespace std;


class Model
{
public:

	vector<float> instances;
	vector<glm::vec2> offsetInstances;
	int instanceCount;
	vector<float> grassLength;

    unsigned int sizeX;
    unsigned int sizeZ;
	float lengthX;
	float lengthZ;

	void setupModel(unsigned int sizeX, unsigned int sizeZ, float lengthX, float lengthZ, glm::vec3 position, float height);
	void Draw();

	void printVertices();


	void setOffsetInstances(vector<glm::vec2> offsetInstances);
	void setInstanceCount(int instanceCount);

	void setMatrix(glm::mat4 modelMatrix);
	glm::mat4 getMatrix();


	int getInstanceCount();

	glm::mat4 matrix = glm::mat4(1.0);

private:

	GLuint EBO, VBO, VAO, instanceVBO, offsetInsVBO, lengthVBO;

	string directory;

};


#endif
