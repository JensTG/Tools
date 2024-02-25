#ifndef VAO_H
#define VAO_H

#ifndef SHAPE_PATH
#define SHAPE_PATH "C:/VSC_PRO_B/OpenGL/resources/shapes/"
#endif

#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class VAO
{
    public:
    unsigned int ID = 0;
    unsigned int nInd = 0;

    VAO();

    VAO(vector<float> vertices, vector<unsigned int> indices)
    {
        nInd = indices.size();

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &ID);

        // 1. bind Vertex Array Object
        glBindVertexArray(ID);
        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        // 3. copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
        // 4. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    VAO(string shapePath)
    {
        vector<float> vertices;
        vector<unsigned int> indices;

        // Define variables for use:
        string vData;
        ifstream vFile;

        // Ensure ifstreams can throw exceptions:
        vFile.exceptions(ifstream::failbit | ifstream::badbit);

        // Process files:
        try
        {
            shapePath = SHAPE_PATH + shapePath + ".v";
            cout << "Vertices loaded: " << shapePath << endl;
            vFile.open(shapePath.c_str());
            stringstream vStream;
            vStream << vFile.rdbuf();
            vFile.close();
            vData = vStream.str();
        }
        catch(ifstream::failure e)
        {
            cout << "ERROR: Vertice data not read: " << e.what() << endl;
        }
        
        size_t index = 0;
        vData.erase(remove_if(vData.begin(), vData.end(), ::isspace), vData.end());
        while(true)
        {
            float value = stof(vData, &index);
            vertices.push_back(value);
            if(vData.length() > index)
                vData = vData.substr(index + 1);
            else break;
        }

        string iData;
        ifstream iFile;
        iFile.exceptions(ifstream::failbit | ifstream::badbit);
        try
        {
            shapePath.pop_back();
            shapePath += "i";
            cout << "Indices loaded: " << shapePath << endl;
            iFile.open(shapePath.c_str());
            stringstream iStream;
            iStream << iFile.rdbuf();
            iFile.close();
            iData = iStream.str();
        }
        catch(ifstream::failure e)
        {
            cout << "ERROR: Indice data not read: " << e.what() << endl;
        }
        index = 0;
        iData.erase(remove_if(iData.begin(), iData.end(), ::isspace), iData.end());
        while(true)
        {
            unsigned int value = (unsigned int)stof(iData, &index);
            indices.push_back(value);
            if(iData.length() > index)
                iData = iData.substr(index + 1);
            else break;
        }

        if(vertices.size() % 3 != 0)
            cout << "ERROR: Incorrect number of vertice components" << endl;
        if(indices.size() % 3 != 0)
            cout << "ERROR: Incorrect number of indices" << endl;
        
        nInd = indices.size();

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &ID);

        // 1. bind Vertex Array Object
        glBindVertexArray(ID);
        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        // 3. copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
        // 4. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    
    void bind()
    {
        glBindVertexArray(ID);
    }
};

#endif