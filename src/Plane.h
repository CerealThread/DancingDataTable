#ifndef PLANE_H
#define PLANE_H


#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <glm/mat3x3.hpp>
#include "glm/ext.hpp"


class Plane
{
    public:

    Plane(unsigned int sizeX, unsigned int sizeZ, glm::vec3 position)
    {
        float side = 1.0f;
	    plane_vertices = { 
								-side, 0.0,  side, 1.0, //0
								 side, 0.0,  side, 1.0,  //1
								-side, 0.0, -side, 1.0, //2
								 side, 0.0, -side, 1.0,//3

	                           };
	    plane_colors = {
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		
	    };
        plane_indices = { 0, 1, 2, 2, 3, 1};

		this->sizeX = sizeX;
		this->sizeZ = sizeZ;
		this->position = position;

		setBuffers();
    }

    Plane()
    {

		this->sizeX = 10;
		this->sizeZ = 10;
		this->position = glm::vec3(0.0, 0.0, 0.0);

        float side = 1.0f;

	    plane_vertices = { 
								-side, 0.0,  side, 1.0, //0
								 side, 0.0,  side, 1.0,  //1
								-side, 0.0, -side, 1.0, //2
								 side, 0.0, -side, 1.0,//3

	                           };
	    plane_colors = {
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		    0.0, 0.2, 0.0, 1.0,
		
	    };
        plane_indices = { 0, 1, 2, 2, 3, 1};



		setBuffers();
    }


	void drawPlane();
	void setMatrix(glm::mat4 model);
	glm::mat4 getMatrix();


private:

	void setBuffers();
	
    unsigned int handle[3];

	GLuint plane_vao;
	std::vector<GLfloat> plane_vertices;
	std::vector<GLfloat> plane_colors;
	std::vector<GLuint> plane_indices;

	glm::mat4 model;

	unsigned int sizeX, sizeZ;
	glm::vec3 position;
};

#endif