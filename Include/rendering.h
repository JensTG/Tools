#ifndef RENDERFUNCS
#define RENDERFUNCS

#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <massInclude/assimp.h>

#include <shader.h>
#include <VAO.h>
#include <mesh.h>
#include <model.h>
using namespace std;

template<typename T>
vector<T> fileToVector(string filePath)
{
    ifstream file(filePath);
    vector<T> values;

    T value;
    while(file >> value)
        values.push_back(value);

    return values;
}

vector<float> transformVector(vector<float> vertices, glm::mat4 trans)
{
    glm::vec4 temp;
    for(int i = 0; i < vertices.size(); i += 3)
    {
        temp = glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);
        temp = trans * temp;
        vertices[i] = temp.x;
        vertices[i + 1] = temp.y;
        vertices[i + 2] = temp.z;
    }
    return vertices;
}
vector<unsigned int> transformVector(vector<unsigned int> indices, int offset)
{
    for(int i = 0; i < indices.size(); i++)
    {
        indices[i] += offset;
    }
    return indices;
}

#endif