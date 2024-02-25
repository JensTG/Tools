#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <VAO.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

class Model
{
    public:
    VAO shape = VAO();
    vec3 position = vec3(1.0f, 1.0f, 1.0f);
    vec3 scale = vec3(1.0f, 1.0f, 1.0f);
    vec3 rotation = vec3(1.0f, 1.0f, 1.0f);
    Model(VAO form, vec3 pos, vec3 s, vec3 rot)
    {
        shape = form;
        position = pos;
        scale = s;
        rotation = rot;
    }
};
class Collection
{
    // Format:
    // shape, posX, posY, posZ, scaleX, scaleY, scaleZ, degrees, rotX, rotY, rotZ 
    // cube, 0.0, 2.3, 3.5, 1.0, 1.0, 1.0, 30.0, 1.0, 0.0, 0.0

    public:
    vector<Model> models = {};

    /*
        input: The path to the .col file and optionally scales every shape in the map
    */
    Collection(string colPath, vec3 gMove = vec3(1.0f, 1.0f, 1.0f), vec3 gScale = vec3(1.0f, 1.0f, 1.0f), vec3 gRot = vec3(1.0f, 1.0f, 1.0f))
    {
        
    }

};

#endif