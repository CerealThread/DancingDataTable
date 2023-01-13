#include "Plane.h"


void Plane::drawPlane() {
	glBindVertexArray(plane_vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Plane::setBuffers() {
	    glGenVertexArrays(1, &plane_vao);
	    glBindVertexArray(plane_vao);
    
	    glGenBuffers(3, handle);
    
	    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices) * sizeof(GLfloat), &plane_vertices[0], GL_STATIC_DRAW);
	    glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	    glEnableVertexAttribArray(0);  // Vertex position
    
	    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_colors) * sizeof(GLfloat), &plane_colors[0], GL_STATIC_DRAW);
	    glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	    glEnableVertexAttribArray(1);  // Vertex normal
    
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plane_indices) * sizeof(unsigned int), &plane_indices[0], GL_STATIC_DRAW);
    
	    glBindVertexArray(0);
}

void Plane::setMatrix(glm::mat4 model)
{
	this->model = model;
}

glm::mat4 Plane::getMatrix()
{
	return this->model;
}
