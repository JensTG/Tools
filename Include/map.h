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

vector<VAO> readCollection(string filePath, bool fullPath = false)
{
    if(!fullPath)
    {
        string basePath = "C:/VSC_PRO_B/OpenGL/resources/collections/";
        filePath = basePath.append(filePath.append(".col"));
    }
    vector<VAO> shapes = {};
    ifstream file(filePath.c_str());
    
    float posX, posY, posZ, scaleX, scaleY, scaleZ, degrees, rotX, rotY, rotZ;
    string shapePath;
    while (file >> shapePath >> posX >> posY >> posZ >> scaleX >> scaleY >> scaleZ >> degrees >> rotX >> rotY >> rotZ)
    {
        cout << "C:/VSC_PRO_B/OpenGL/resources/shapes/" + shapePath + ".v" << endl;
        vector<float> ver = fileToVector<float>("C:/VSC_PRO_B/OpenGL/resources/shapes/" + shapePath + ".v");
        vector<unsigned int> ind = fileToVector<unsigned int>("C:/VSC_PRO_B/OpenGL/resources/shapes/" + shapePath + ".i");
        
        mat4 trans = mat4(1.0f);
        trans = translate(trans, vec3(posX, posY, posZ));
        trans = rotate(trans, radians(degrees), vec3(rotX, rotY, rotZ));
        trans = scale(trans, vec3(scaleX, scaleY, scaleZ));

        shapes.push_back(VAO(ver, ind, trans));
    }

    return shapes;
}

#endif