#ifndef RENDERFUNCS
#define RENDERFUNCS

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
using namespace glm;
using namespace std;

template<typename T>
vector<T> fileToVector(string filePath)
{
    ifstream file;
    string data;
    vector<T> values;
    // Ensure ifstreams can throw exceptions:
    file.exceptions(ifstream::failbit | ifstream::badbit);

    // Process files:
    try
    {
        file.open(filePath.c_str());
        stringstream stream;
        stream << file.rdbuf();
        file.close();
        data = stream.str();
    }
    catch(ifstream::failure e)
    {
        cout << "ERROR: Vector data not read: " << e.what() << endl;
    }
    
    size_t index = 0;
    data.erase(remove_if(data.begin(), data.end(), ::isspace), data.end());
    while(true)
    {
        T value = (T)stof(data, &index);
        values.push_back(value);
        if(data.length() > index)
            data = data.substr(index + 1);
        else break;
    }
    return values;
}

vector<float> transformVector(vector<float> vertices, mat4 trans)
{
    vec4 temp;
    for(int i = 0; i < vertices.size(); i += 3)
    {
        temp = vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1);
        temp *= trans;
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