#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include <VAO.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

// Perhaps use readline to get data
// Format:
// C:\VSC_PRO_B\OpenGL\resources\shapes\shape, posX, posY, posZ, scaleX, scaleY, scaleZ, degrees, rotX, rotY, rotZ 
// C:\VSC_PRO_B\OpenGL\resources\shapes\cube, 0.0, 2.3, 3.5, 1.0, 1.0, 1.0, 30.0, 1.0, 0.0, 0.0

// Multiply vertices by translation, scale and rotation. Combine all vertices and indices, and make VAO for a static environment

vector<VAO> readCollection(string filePath)
{
    vector<VAO> shapes = {};
    ifstream file(filePath.c_str());
    
    float posX, posY, posZ, scaleX, scaleY, scaleZ, degrees, rotX, rotY, rotZ;
    string shapePath;
    while (file >> shapePath >> posX >> posY >> posZ >> scaleX >> scaleY >> scaleZ >> degrees >> rotX >> rotY >> rotZ)
    {
        vector<float> ver = fileToVector<float>(shapePath + ".v");
        vector<unsigned int> ind = fileToVector<unsigned int>(shapePath + ".i");
        
        mat4 trans = mat4(1.0f);
        trans = translate(trans, vec3(posX, posY, posZ));
        trans = rotate(trans, radians(degrees), vec3(rotX, rotY, rotZ));
        trans = scale(trans, vec3(scaleX, scaleY, scaleZ));
        ver = transformVector(ver, trans);

        shapes.push_back(VAO(ver, ind));
    }

    return shapes;
}

#endif