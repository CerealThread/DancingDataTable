#ifndef FIELD_H
#define FIELD_H

#include <glm/mat3x3.hpp>
#include "Model.h"
#include "Plane.h"

class Field {

public:


    Field(unsigned int modelCountX, unsigned int modelCountZ, float lengthX, float lengthZ, glm::vec3 position, float data)
    {
        this->modelCountX = modelCountX;
        this->modelCountZ = modelCountZ;
        this->lengthX = lengthX;
        this->lengthZ = lengthZ;
        this->position = position;
        this->speed = data;

        Model model1;

	    model1.setupModel(modelCountX, modelCountZ, lengthX, lengthZ, position, data);

        model = model1;

        this->color = glm::vec3(data, 1-data, 0);

        Plane plane(lengthX, lengthZ, position);
        this->plane = plane;
    }

    void genOffsetInstances();
    void Draw();
    void drawPlane();

    void setPosition(glm::vec3 pos);
    void setPlaneMatrix(glm::mat4 model);
    void setModelMatrix(glm::mat4 model);

    glm::mat4 getPlaneMatrix();
    glm::mat4 getModelMatrix();

    glm::vec3 getColor();

private:
        Plane plane;
        Model model;
        unsigned int modelCountX;
        unsigned int modelCountZ;
        float lengthX;
        float lengthZ;
        glm::vec3 position;
        float speed;
        glm::vec3 color;
};


#endif