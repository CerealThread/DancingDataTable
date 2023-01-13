#include "FieldController.h"
#include <fstream>
#include <istream>
#include <string>

vector<vector<float>> FieldController::normalizeData(vector<vector<float>> data)
{
    vector<vector<float>> normalizedData;

    for(int i = 0; i < data[0].size(); i++) {
        float largest = 0;
        float smallest = std::numeric_limits<float>::max();
        vector<float> normData;


        for(int j = 0; j < data.size(); j++) {

            if(data[j][i] > largest) {
                largest = data[j][i];
            }

            if(data[j][i] < smallest) {
                smallest = data[j][i];
            }
        }
        float div = largest - smallest;

        for(int k = 0; k < data.size(); k++) {

            normData.push_back((data[k][i] - smallest) / div);
        }
        normalizedData.push_back(normData);
    }

    return normalizedData;
}

void FieldController::makeFields(string filename)
{
    vector<vector<float>> data = readFile(filename);

    dataElementsX = data[0].size();
    dataElementsZ = data.size();

    vector<vector<float>> normalizedData = normalizeData(data);


    lengthX = 20;
    lengthZ = 20;



    float fieldLengthX = this->lengthX / dataElementsX;
    float fieldLengthZ = this->lengthZ / dataElementsZ;

    int modelNumX = modelDensity * fieldLengthX;
    int modelNumZ = modelDensity * fieldLengthZ;

    float xMargin = margin;
    float zMargin = margin;


    for(int i = 0; i < dataElementsZ; i++) {
        for(int j = 0; j < dataElementsX; j++) {

            glm::vec3 fieldPos = glm::vec3((float)j * (fieldLengthX + xMargin), 0, (float)i * (fieldLengthZ + zMargin));

            Field field(modelNumX, modelNumZ, fieldLengthX, fieldLengthZ, fieldPos, normalizedData[j][i]);

            fields.push_back(field);

        }
    }
}


vector<vector<float>> FieldController::readFile(string filename)
{
    vector<vector<float>> data;

    fstream file;
    file.open(filename, ios::in);
    if(!file)
    {
        std::cout << "Error reading data file" << std::endl;
    }
    else {

        vector<string> lines;
        string line;

        while(!file.eof())
        {
            getline(file, line);

            lines.push_back(line);
        }

        size_t pos = 0;
        string token;

        for(int i = 0;i < lines.size() - 1; i++) {
            
            pos = lines[i].find(',');
            lines[i].erase(0, pos + 1);


            vector<float> subData;

            while((pos = lines[i].find(',')) != std::string::npos) {
                token = lines[i].substr(0, pos);

                float value = std::stof(token);
                
                subData.push_back(value);

                lines[i].erase(0, pos + 1);
            }

            float value = std::stof(lines[i]);
            subData.push_back(value);

            data.push_back(subData);
        }
    }
    file.close();

    return data;
}

void FieldController::loadShaders() {
    shader.loadShaders("resources/shader.vert", "resources/shader.frag");
	basicShader.loadShaders("resources/basicshader.vs", "resources/basicshader.fs");
}


void FieldController::genOffsetInstances() {
    for(auto & element: fields)
    {
        element.genOffsetInstances();
    }
}




void FieldController::DrawFields()
{
    int count = 0;

    for(auto & element: fields) {

        shader.use();


	    model = glm::mat4(1.0);
    
	    element.setModelMatrix(model);
	    model = element.getModelMatrix();
        view = cameras[camNum].getViewMatrix();

	    shader.setUniform("model", model);
	    shader.setUniform("view", view);
	    shader.setUniform("projection", projection);


        shader.setUniform("color", element.getColor());

	    element.Draw();


        basicShader.use();

        model = glm::mat4(1.0);

	    element.setPlaneMatrix(model);

	    model = element.getPlaneMatrix();

	    basicShader.setUniform("model", model);
	    basicShader.setUniform("view", view);
	    basicShader.setUniform("projection", projection);



	    element.drawPlane();
    }
}

void FieldController::setNextCam() {
    if(camNum == 4) {
        camNum = 1;
    }
    else {
        camNum += 1;
    }
}


FirstPersonCamera FieldController::getCamera()
{
    return this->cameras[camNum];
}

void FieldController::rotateCamera(float yaw, float pitch)
{
    this->cameras[camNum].rotate(yaw, pitch);
}

