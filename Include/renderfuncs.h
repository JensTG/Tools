#ifndef RFUNCS
#define RFUNCS
#include <VAO.h>
#include <vector>
#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h>

float largestCoord(vector<float> vertices, int offset, int stride = 3) 
{
    float largest = 0;
    for(int i = offset; i < vertices.size(); i += stride)
    {
        largest = vertices[i] > largest ? vertices[i] : largest;
    }
    return largest;
}
float largestCoord(VAO vao, int offset, int stride = 3) 
{
    vector<float> vertices = vao.vertices;
    return largestCoord(vertices, offset, stride);
}

#endif