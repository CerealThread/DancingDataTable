#include "Model.h"
#include "ModelData.h"
#include "FastNoiseLite.h"

#include <iostream>
#include <fstream>

#include <string>



void Model::setOffsetInstances(vector<glm::vec2> offsetIns)
{
	offsetInstances.assign(offsetIns.begin(), offsetIns.end());
}
void Model::setInstanceCount(int insCount)
{
	instanceCount = insCount;
}

void Model::setMatrix(glm::mat4 modelMatrix)
{
	this->matrix = modelMatrix;
}

glm::mat4 Model::getMatrix()
{
	return matrix;
}


int Model::getInstanceCount()
{
	return instanceCount;
}

void Model::Draw()
{

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, offsetInsVBO);


	glBufferSubData(GL_ARRAY_BUFFER, 0, offsetInstances.size() * sizeof(glm::vec2), &offsetInstances[0]);


   	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instanceCount);
    glBindVertexArray(0);
}

void Model::setupModel(unsigned int sizeX, unsigned int sizeZ, float lengthX, float lengthZ, glm::vec3 position, float height)
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	this->sizeX = sizeX;
	this->sizeZ = sizeZ;
	this->lengthX = lengthX;
	this->lengthZ = lengthZ;

	float resolutionX = lengthX / sizeX;
	float resolutionZ = lengthZ / sizeZ;
	
	instanceCount = this->sizeX * this->sizeZ;
	for(unsigned int i = 0; i < this->sizeX; i++) {
		for(unsigned int j = 0; j < this->sizeZ; j++) {
			instances.push_back((((float)i)*resolutionX) - lengthX/2);
			instances.push_back(0);
			instances.push_back((((float)j)*resolutionZ) - lengthZ/2);

			float heightnoise = noise.GetNoise((float) i, (float) j);
			grassLength.push_back(height * 1.2 + 0.01);

			offsetInstances.push_back(glm::vec2(0.0f, 0.0f));
		}
	}
	
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
	glGenBuffers(1, &instanceVBO);
	glGenBuffers(1, &offsetInsVBO);
	glGenBuffers(1, &lengthVBO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(float), &instances[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(1, 1);


	glBindBuffer(GL_ARRAY_BUFFER, lengthVBO);
	glBufferData(GL_ARRAY_BUFFER, grassLength.size() * sizeof(float), &grassLength[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(3, 1);


	glBindBuffer(GL_ARRAY_BUFFER, offsetInsVBO);
	glBufferData(GL_ARRAY_BUFFER, offsetInstances.size() * sizeof(glm::vec2), &offsetInstances[0], GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Model::printVertices()
{
	ofstream file("text2.txt");
	if(file.is_open())
	{
		file << "indices[] = {";
	
		for(int i = 0; i < indices.size(); i++)
		{
			file << indices[i] << ", ";
			if(i % 6 == 0)
			file << std::endl;
		}

		file << "}";
	}
}
