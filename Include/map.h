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

// Perhaps use readline to get data
// Format:
// shape, posX, posY, posZ, scaleX, scaleY, scaleZ, degrees, rotX, rotY, rotZ 
// cube, 0.0, 2.3, 3.5, 1.0, 1.0, 1.0, 30.0, 1.0, 0.0, 0.0

// Multiply vertices by translation, scale and rotation. Combine all vertices and indices, and make VAO for a static environment

#endif