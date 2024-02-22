#pragma once
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
    vector<float> vertices = {};
    vector<unsigned int> indices = {};

    VAO(vector<float> ver, vector<unsigned int> ind)
    {
        vertices = ver;
        indices = ind;

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
    VAO(string shapePath, bool fullPath = false)
    {
        vector<float> ver;
        vector<unsigned int> ind;

        // Define variables for use:
        string vData;
        ifstream vFile;

        // Ensure ifstreams can throw exceptions:
        vFile.exceptions(ifstream::failbit | ifstream::badbit);

        // Process files:
        try
        {
            if(!fullPath) shapePath = SHAPE_PATH + shapePath; 
            vFile.open(shapePath.append(".v").c_str());
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
            try {float value = stof(vData, &index);}
            catch {break;}
            ver.push_back(value);
            cout << value << endl;
            if(vData.length() > index)
                vData = vData.substr(index + 1);
            else break;
        }

        string iData;
        ifstream iFile;
        iFile.exceptions(ifstream::failbit | ifstream::badbit);
        try
        {
            iFile.open(shapePath.append(".i").c_str());
            stringstream iStream;
            iStream << iFile.rdbuf();
            iFile.close();
            iData = iStream.str();
        }
        catch(ifstream::failure e)
        {
            cout << "ERROR: Indice data not read: " << e.what() << endl;
        }
    }
    void bind()
    {
        glBindVertexArray(ID);
    }
};

#endif