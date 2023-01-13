#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Shader.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	unsigned int id;
	string path;
	std::string type;
};

class Mesh
{
public:
	unsigned int VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader &shader);

private:
	unsigned int VBO, EBO;

	void setupMesh();
};

#endif