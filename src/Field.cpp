#include "Field.h"
#include "FastNoiseLite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


void Field::Draw()
{
    model.Draw();
}

void Field::drawPlane()
{
	plane.drawPlane();
}

glm::vec3 Field::getColor() {
	return color;
}



void Field::genOffsetInstances()
{
	int time = glutGet(GLUT_ELAPSED_TIME)/15.0f;


    FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);


	std::vector<glm::vec2> offsetInstances;

	for(int i = 0; i < modelCountX; i++) {
		for(int j = 0; j < modelCountZ; j++) {

			float noiseParam1 = i*20;
			float noiseParam2 = (time * (speed + 0.1) * 2);
			float noiseParam3 = j*20;

			float posOffsetX = noise.GetNoise((float)noiseParam1, (float)noiseParam2, (float)noiseParam3);
			float posOffsetZ = noise.GetNoise((float)noiseParam1+1000, (float)noiseParam2+1000, (float)noiseParam3+1000);

			offsetInstances.push_back(glm::vec2(posOffsetX, posOffsetZ));
		}
	}

    model.setOffsetInstances(offsetInstances);
}

void Field::setPlaneMatrix(glm::mat4 model)
{
	model = glm::translate(model, position - glm::vec3(lengthX/modelCountX/2, 0, lengthZ/modelCountZ/2));

	model = glm::scale(model, glm::vec3(lengthX/2, 1, lengthZ/2));
	plane.setMatrix(model);
}

void Field::setModelMatrix(glm::mat4 modelMatrix)
{
	modelMatrix = glm::translate(modelMatrix, position);
	model.setMatrix(modelMatrix);
}

void Field::setPosition(glm::vec3 pos)
{
	this->position = pos;
}


glm::mat4 Field::getPlaneMatrix()
{
	return plane.getMatrix();
}

glm::mat4 Field::getModelMatrix()
{
	return model.getMatrix();
}