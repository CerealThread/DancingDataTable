#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include "Field.h"
#include "Camera.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class FieldController
{
public:

    FieldController(int width, int height)
    {
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        lengthX = 20;
        lengthZ = 20;

        FirstPersonCamera camera0(glm::vec3(lengthX/2-2.5, 28.0f, lengthZ/2+2.5), 0.0, -3.1415/2);
        FirstPersonCamera camera1(glm::vec3(lengthX, 3.0f, lengthZ), -3.1415/2, -3.1415/4);
        FirstPersonCamera camera2(glm::vec3(0.0, 3.0f, lengthZ), 3.1415/2, -3.1415/4);
        FirstPersonCamera camera3(glm::vec3(lengthX, 3.0f, 0.0), -3.1415/2, -3.1415/4);
        FirstPersonCamera camera4(glm::vec3(0.0, 3.0f, 0.0), 0, -3.1415/4);

        cameras.push_back(camera0);
        cameras.push_back(camera1);
        cameras.push_back(camera2);
        cameras.push_back(camera3);
        cameras.push_back(camera4);

        camNum = 1;
        cameras[camNum] = camera1;



        margin = 0.1;


        view = cameras[camNum].getViewMatrix();
    	projection = glm::perspective(glm::radians(cameras[camNum].getFOV()), (float)width / (float)height, 0.1f, 100.0f);	

	    model = glm::mat4(1.0);
    }

    FieldController(int width, int height, int lengthX, int lengthZ)
    {
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);

        this->lengthX = lengthX;
        this->lengthZ = lengthZ;

        FirstPersonCamera camera0(glm::vec3(lengthX/2, 28.0f, lengthZ/2), 0.0, -3.1415/2);
        FirstPersonCamera camera1(glm::vec3(lengthX, 5.0f, lengthZ), -3.1415/2, -3.1415/4);
        FirstPersonCamera camera2(glm::vec3(0.0, 5.0f, lengthZ), 3.1415/2, -3.1415/4);
        FirstPersonCamera camera3(glm::vec3(lengthX, 5.0f, 0.0), -3.1415/2, -3.1415/4);
        FirstPersonCamera camera4(glm::vec3(0.0, 5.0f, 0.0), 0, -3.1415/4);

        cameras.push_back(camera0);
        cameras.push_back(camera1);
        cameras.push_back(camera2);
        cameras.push_back(camera3);
        cameras.push_back(camera4);

        camNum = 1;
        cameras[camNum] = camera1;



        margin = 0.1;


        view = cameras[camNum].getViewMatrix();
    	projection = glm::perspective(glm::radians(cameras[camNum].getFOV()), (float)width / (float)height, 0.1f, 100.0f);	

	    model = glm::mat4(1.0);
    }

    unsigned int camNum;

    // void printView();
    void rotateCamera(float yaw, float pitch);


    void loadShaders();

    void makeFields(string filename);

    void setNextCam();
    void setPrevCam();


    void DrawFields();

    FirstPersonCamera getCamera();

    void genOffsetInstances();

private:

    vector<vector<float>> readFile(string filename);
    vector<vector<float>> normalizeData(vector<vector<float>> data);


    float lengthX, lengthZ, dataElementsX, dataElementsZ;

    std::vector<Field> fields;
    float margin;

    float modelDensity = 10;


    Shader shader;
    Shader basicShader;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    std::vector<FirstPersonCamera> cameras;
};


#endif